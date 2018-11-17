void _memr(int arg0, int arg1, int arg2, int arg3) {
    var_8 = arg0;
    var_C = arg1;
    var_18 = arg2;
    var_20 = arg3;
    if (var_18 != 0x0) {
            var_C = var_C % 0x1000;
            if (var_C < 0x0) {
                    var_C = var_C + 0x1000;
            }
            if (sign_extend_64(var_C) + var_18 < 0x1001) {
                    __memcpy_chk(var_20, var_8 + sign_extend_64(var_C), var_18, 0xffffffffffffffff);
            }
            else {
                    __memcpy_chk(var_20, var_8 + sign_extend_64(var_C), sign_extend_64(0x1000 - var_C), 0xffffffffffffffff);
                    __memcpy_chk(var_20 + sign_extend_64(0x1000 - var_C), var_8, var_18 - sign_extend_64(0x1000 - var_C), 0xffffffffffffffff);
            }
    }
    return;
}

int _memr_1(int arg0, int arg1) {
    _memr(arg0, arg1, 0x1, var_D);
    rax = sign_extend_64(var_D);
    return rax;
}

int _memr_2(int arg0, int arg1) {
    _memr(arg0, arg1, 0x2, var_E);
    _reverse_endian(var_E, 0x2);
    rax = sign_extend_64(var_E);
    return rax;
}
int _memr_4(int arg0, int arg1) {
    _memr(arg0, arg1, 0x4, var_10);
    _reverse_endian(var_10, 0x4);
    rax = var_10;
    return rax;
}