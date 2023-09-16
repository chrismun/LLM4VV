V34 :0x24 acc_test_module
12 acc_wait.F90 S624 0
09/15/2023  13:55:09
use iso_c_binding public 0 indirect
use nvf_acc_common public 0 indirect
use openacc_la public 0 direct
enduse
D 58 26 646 8 645 7
D 67 26 649 8 648 7
D 76 26 646 8 645 7
D 97 26 743 8 742 7
S 624 24 0 0 0 9 1 0 5013 10005 0 A 0 0 0 0 B 0 2 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 acc_test_module
R 645 25 7 iso_c_binding c_ptr
R 646 5 8 iso_c_binding val c_ptr
R 648 25 10 iso_c_binding c_funptr
R 649 5 11 iso_c_binding val c_funptr
R 683 6 45 iso_c_binding c_null_ptr$ac
R 685 6 47 iso_c_binding c_null_funptr$ac
R 686 26 48 iso_c_binding ==
R 688 26 50 iso_c_binding !=
R 742 25 6 nvf_acc_common c_devptr
R 743 5 7 nvf_acc_common cptr c_devptr
R 749 6 13 nvf_acc_common c_null_devptr$ac
R 787 26 51 nvf_acc_common =
A 68 1 0 0 0 58 683 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
A 71 1 0 0 0 67 685 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
A 141 1 0 0 0 97 749 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
Z
J 133 1 1
V 68 58 7 0
S 0 58 0 0 0
A 0 6 0 0 1 2 0
J 134 1 1
V 71 67 7 0
S 0 67 0 0 0
A 0 6 0 0 1 2 0
J 36 1 1
V 141 97 7 0
S 0 97 0 0 0
A 0 76 0 0 1 68 0
Z
