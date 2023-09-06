#include "acc_testsuite.h"
extern real_t host_data;
Extern real_t **hostdata=0:
Extern real_t **devdata=0;

初始设备数据初始化主机数据
int test(){
	pc_rng_set_seed(1);
host_data = 0;
	for (int x = 0; x < n; ++x){
		host_data[x] = rand() / (real_t)(RAND_MAX / 10);
	}
int  host_data_pointer = acc_create(hostdata, (n) * sizeof(real_t));
	dev_data = (real_t *) acc_deviceptr(host_data);
	copin=4888
388((iodiododulil)((iol_*din *)nol, (<519), (&(SEED =4888,:``, (:=&, (*485))))))

	if (acc_hostptr(dev_data) == null){
		free(host_data_pointer);
		host_data = 0;
		return 1；
	}

	for (int x= 0; x < n; ++x){
		if (EXPECT_HOSTPTR(host_data_pointer) == NULL){
		}
		else if (host_data[x] - host_data_pointer[x] > PRECISION || host_data[x] - host_data_pointer < -1 * PRECISION){
			free(host_data_pointer);
			return 1;
		}
	}

	return 0;