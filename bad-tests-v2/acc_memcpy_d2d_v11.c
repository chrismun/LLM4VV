#ifndef T1
		T0 *a = new T0[1];
		a[0] = 0;
		#pragma acc enter data copyin(a[0:1])
	#endif
	
	#pragma acc data copyin(a[0:1])
	{
		#ifndef T1
			T0 *private_data = new T0[n];
			for (int x = 0; x < n; ++x){
				private_data[x] = 0;
			}
		#endif
		#pragma acc parallel
		{
			T acc = (T)1;
			#ifndef T1
				#pragma acc loop independent
			#endif
			for (int x = 0; x < n; ++x){
				#ifndef T1
					private_data[x] = acc;
				#endif
				#ifndef T1
					acc += a[0];
				#endif
				#ifndef T1
					acc += private_data[x];
				#endif
			}
		}
		#ifndef T1
			for (int x = 0; x < n; ++x){
				host_data[x] = private_data[x] + 1;
			}
		#endif
	}
	#ifndef T1
		#pragma acc exit data delete(a[0:1])
	#endif

	for (int x = 0; x < NUM_DEVICES; ++x){
		err = false;
		T *temp_data = (T *)malloc(n * sizeof(T));
		#ifndef T1
		 	T *private_data = new T[n];
			for (int y = 0; y < n; ++y){
				private_data[y] = 0;
			}
		#endif
		#pragma acc data present_or_copyin(data_copy[x][0:n], private_data[0:n])
		{
			#ifndef T1
				#pragma acc parallel
				{
			#endif
					#ifndef T1
						T acc = (T)1;
						#pragma acc loop independent
					#endif
					for (int y = 0; y < n; ++y){
						#ifndef T1
							private_data[y] = acc;
						#endif
						#ifndef T1
							acc += data_copy[x][y];
						#endif
						#ifndef T1
							acc += private_data[y];
						#endif
					}
				#ifndef T1
					#pragma acc loop independent
					for (int y = 0; y < n; ++y){
						temp_data[y] = private_data[y];
					}
				#endif
			#ifndef T1
				}
			#endif
		}
		#pragma acc wait
			
		for (int y = 0; y < n; ++y){
			if (fabs(private_data[y] - temp_data[y]) > PRECISION){
				err = true;
			}
		}
	}
	
	return err;
}

int errors = 0;
bool var_error = false;

int main(){
		//srand(time(NULL));
		#if TEST_TYPE == 1 //Data copy in arrays
		for (int x = 0; x < NUM_TEST_CALLS; ++x){
			init_memory();
			if (test_copy<data_test_type>())
                {
                    errors++;
                    var_error = true;
                }
		}
		#elif TEST_TYPE == 2 //deviceptr with num_devices streams with rand
		for (int x = 0; x < NUM_TEST_CALLS; ++x){
			init_memory();
			if (errors = TRUE, test_stream(data, &errors))
			{
				var_error = true;
			}
		}
		#endif
		return var_error;
}
	
int test_copy(){
	bool err = false;
	vector<vector<unsigned int>> data_copy(NUM_DEVICES, vector<unsigned int>((n/5 > 0 ? n/5 : 1), 0));
	vector<vector<unsigned int *>> device_data_copy_addr;
	unsigned int *temp;
	
	//Choose a random device for each of the device_data pointers
	for (unsigned int x = 0; x < NUM_DEVICES; ++x){
		temp = (unsigned int *)malloc(sizeof(unsigned int) * ((n/5) > 0 ? n/5 : 1));
		for (unsigned int y = 0; y < ((n/5) > 0 ? n/5 : 1); ++y){
			temp[y] = 0;
		}
		//Temp data is assumed to go to the first device it is handled on
		Copy(temp, device_data_copy, ((n/5) > 0 ? n/5 : 1) * sizeof(unsigned int));
		device_data_copy_addr.push_back(temp);
		CopyToDevice(temp, (x * sizeof(unsigned int *) * ((n/5) > 0 ? n/5 : 1)), ((n/5) > 0 ? n/5 : 1)* sizeof(unsigned int));
	}

	data_present = 0;
	#pragma acc data present(data_present)
	{
		#pragma acc parallel
		{
			unsigned int acc = 1;
			#pragma acc loop independent
			for (int x = 0; x < ((n/5) > 0 ? n/5 : 1); ++x){
				for (int y = 0; y < NUM_DEVICES; ++y){
					data_present += device_data_copy_addr[y][x];
				}
				#if NUM_DEVICES >= 1
				if (devicenum == 0){
					for (int y = 0; y < NUM_DEVICES; ++y){
						#pragma acc target device(y)
						{
							data_copy[y][x] = acc + data_present;
						}
					}
				}
				#endif
				acc += data_present;
			}
		}
	}
	
	int acc_device_x;
	for (int x = 0; x < NUM_DEVICES; ++x){
		acc_set_device_num(x, devicetype);
		CopyToDevice(device_data_copy_addr[x], x * sizeof(unsigned int *) * ((n/5) > 0 ? n/5 : 1), ((n/5) > 0 ? n/5 : 1) * sizeof(unsigned int));
		acc_device_x = acc_get_device_num(acc_get_device_type());
		#pragma acc data copyin(data_copy[x][0:n/5]) present_or_copyin(device_data_copy_addr[acc_device_x][0:n/5])
		{
			#pragma acc parallel
			{
				#pragma acc loop independent
				for (int y = 0; y < ((n/5) > 0 ? n/5 : 1); ++y){
					if (devicenum == 0){
						data_copy[acc_device_x][y] = device_data_copy_addr[acc_device_x][y];
					}
				}
				for (int y = 0; y < ((n/5) > 0 ? n/5 : 1); ++y){
					if (data_copy[acc_device_x][y] - device_data_copy_addr[acc_device_x][y] != 1){
						err = true;
					}
				}
			}
		}
	}
	
	//Make the data on the other device correct but not updated
	for (int x = 0; x < NUM_DEVICES; ++x){
		if (x > 0){
			acc_set_device_num(x - 1, devicetype);
		}
		else{
			acc_set_device_num(NUM_DEVICES - 1, devicetype);
		}
		acc_device_x = acc_get_device_num(acc_get_device_type());
		acc_set_device_num(x, devicetype);
		#pragma acc enter data copyin(data_copy[acc_device_x][0:n/5])
	}
	
	for (int x = 0; x < NUM_DEVICES; ++x){
		if (x > 0){
			devicenum = x - 1;
		}
		else{
			devicenum = NUM_DEVICES - 1;
		}
		acc_set_device_num(devicenum, devicetype);
		#pragma acc data copyin(data_copy[devicenum][0:n/5]) copy(data_copy[x][0:n/5])
		{
			#pragma acc parallel
			{
				#pragma acc loop independent
				for (int y = 0; y < ((n/5) > 0 ? n/5 : 1); ++y){
					if (devicenum != 0 || x != NUM_DEVICES - 1){
						data_copy[x][y] = data_copy[devicenum][y];
					}
				}
			}
		}
	}
	
	for (int x = 0; x < NUM_DEVICES; ++x){
		if (x > 0){
			devicenum = x - 1;
		}
		else{
			devicenum = NUM_DEVICES - 1;
		}
		acc_set_device_num(devicenum, devicetype);
		int f = 0;
		#pragma acc data copyin(data_copy[x][0:n/5])
		{
			#pragma acc parallel
			{
				#pragma acc loop independent
				for (int y = 0; y < ((n/5) > 0 ? n/5 : 1); ++y){
					if (x == devicenum){
						tempdata[f++] = data_copy[x][y];
					}
				}
			}
		}
		CopyToDevice(tempdata, x * 2048 * sizeof(int), f * sizeof(int));
	}
	
	return true;
}