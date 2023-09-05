void acc_unmap_data(void *data_arg) {
  if (data_arg == NULL) {
    printf("Error: acc_invalid_null_pointer\n");
    return;
  }

  // TODO: Check if data_arg was previously mapped
  // and if the structured reference count is zero
  
  // Unmap the device data
  // TODO: code to unmap the device data

  // Set dynamic reference count to zero
  // TODO: code to set dynamic reference count to zero
}