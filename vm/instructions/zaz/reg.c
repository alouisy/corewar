int _validate_regn(int arg0) {
    var_4 = arg0;
    var_5 = 0x0;
    if (var_4 > 0x0) {
            var_5 = var_4 <= 0x10 ? 0x1 : 0x0;
    }
    rax = var_5 & 0x1 & 0xff;
    return rax;
}

int _regr(int arg0, int arg1) {
    var_10 = arg0;
    var_14 = arg1;
    if (_validate_regn(var_14) != 0x0) {
            var_4 = *(int32_t *)(var_10 + sign_extend_64(var_14 - 0x1) * 0x4 + 0x14);
    }
    else {
            var_4 = 0x0;
    }
    rax = var_4;
    return rax;
}

void _regw(int arg0, int arg1, int arg2) {
    var_8 = arg0;
    var_C = arg1;
    var_10 = arg2;
    if (_validate_regn(var_C) != 0x0) {
            _bout_reg(var_8, var_C, *(int32_t *)(var_8 + sign_extend_64(var_C - 0x1) * 0x4 + 0x14), var_10);
            *(int32_t *)(var_8 + sign_extend_64(var_C - 0x1) * 0x4 + 0x14) = var_10;
    }
    return;
}
