internal.h"

int test_acc_wait_async();
int compare_data(real_t *, real_t *, int, real_t);

int main() {
    int failcode = 0;

    printf("\n\nTesting acc wait async\n\n");
    if (test_acc_wait_async() == 1)
    {
        printf("Failed\n");
        failcode = 1;
    }
    printf("\n\nFinished\n\n");
    return failcode;
}

int test_acc_wait_async()
{
    int failcode, i, j, device_num, totalfailcode;
    int devicenumbers[NUMBER_OF_DEVICES];
    totalfailcode = 0;

    for (device_num = 0; device_num < acc_get_num_devices(acc_device_nvidia); device_num++) {
        acc_set_device_num(device_num, acc_device_nvidia);

        real_t * devicedata[2];
        for (j = 0; j < 2; j++)
        {
            devicedata[j] = (real_t *)malloc(DATA_LENGTH * sizeof(real_t));
            for (i = 0; i < DATA_LENGTH; i++)
            {
                devicedata[j][i] = 1;
            }
        }
        int * queues;
        queues = (int *)malloc(sizeof(int) * NUMBER_OF_QUEUES); 
        devicenumbers[device_num] = 0;
        queues[devicenumbers[device_num]] = 0;
        acc_enqueue_wait_event(queues[devicenumbers[device_num]], devicedata[0], 2 * sizeof(real_t) * DATA_LENGTH, devicenumbers[device_num]);
        acc_enqueue_wait_event(queues[devicenumbers[device_num]], devicedata[1], 2 * sizeof(real_t) * DATA_LENGTH, devicenumbers[device_num]);
        acc_wait_all_async(queues[devicenumbers[device_num]]);
        if (compare_data(devicedata[0], devicedata[1], 2 * DATA_LENGTH, 1) != 0)
        {
            printf("fails array number %d, single queue\n", device_num);
            totalfailcode = 1;
        }

        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < DATA_LENGTH; i++)
            {
                devicedata[j][i] = 1;
            }
        }
        devicenumbers[device_num] = 1;
        queues[devicenumbers[device_num]] = 0;
        acc_enqueue_wait_event(queues[devicenumbers[device_num]], devicedata[devicenumbers[device_num]], sizeof(real_t) * (DATA_LENGTH / 2), devicenumbers[device_num]);
        acc_enqueue_wait_event(queues[devicenumbers[device_num]], &(devicedata[1 - devicenumbers[device_num]])[DATA_LENGTH / 2], sizeof(real_t) * (DATA_LENGTH / 2), devicenumbers[device_num]);
        acc_wait_all_device_async(queues[devicenumbers[device_num]], devicenumbers[device_num]);
        if (compare_data(devicedata[devicenumbers[device_num]], &(devicedata[1 - devicenumbers[device_num]])[DATA_LENGTH / 2], DATA_LENGTH / 2, 1) != 0)
        {
            printf("fails array number %d, multiple queues\n", device_num);
            totalfailcode = 1;
        }

        for (j = 0; j < 2; j++)
        {
            for (i = 0; i < DATA_LENGTH; i++)
            {
                devicedata[j][i] = 1;
            }
        }
        devicenumbers[device_num] = 0;
        queues[0] = 0;
        acc_enqueue_wait_event(queues[0], devicedata[devicenumbers[device_num]], sizeof(real_t) * (DATA_LENGTH / 2), devicenumbers[device_num]);
        acc_enqueue_wait_event(queues[devicenumbers[device_num] + 1], devicedata[1 - devicenumbers[device_num]], sizeof(real_t) * (DATA_LENGTH / 2), devicenumbers[device_num] + 1);
        acc_wait_async(queues[0], queues[devicenumbers[device_num] + 1]);
        if (compare_data(&(devicedata[devicenumbers[device_num]])[DATA_LENGTH / 2], devicedata[1 - devicenumbers[device_num]], DATA_LENGTH / 2, 1) != 0)
        {
            printf("fails array number %d, specifiy queue on multiple devices\n", device_num);
            totalfailcode = 1;
        }
        for (j = 0; j < 2; j++)
        {
            free(devicedata[j]);
        }
    }
    return totalfailcode;
}
int compare_data(real_t * data1, real_t * data2, int length, real_t line)
{
    int j;
    real_t error;
    error = 0;

    for (j = 0; j < length; j++)
    {
        if (data1[j] != data2[j])
        {
            error = error + 1;
        }
    }

    return error;
}