
int _bout_mem_change(int arg0, int arg1, int arg2, int arg3) {
    rax = arg3;
    var_4 = arg0;
    var_10 = arg1;
    var_11 = arg2;
    var_12 = rax;
    if (*(int32_t *)_options != 0x0) {
            _bout_uchar(0x8);
            _bout_uint(var_4);
            _bout_uchar(*(int32_t *)var_10 & 0xff);
            _bout_uchar(*(int32_t *)var_10 & 0xff);
            _bout_uchar(var_11 & 0xff);
            if (*(int32_t *)(_options + 0x18) != 0x0) {
                    var_18 = 0xff;
            }
            else {
                    var_18 = var_12 & 0xff;
            }
            rax = _bout_uchar(var_18 & 0xff);
    }
    return rax;
}

void _memw(int arg0, int arg1, int arg2, int arg3, int arg4) {
    var_8 = arg0;
    var_C = arg1;
    var_18 = arg2;
    var_20 = arg3;
    var_28 = arg4;
    var_30 = malloc(var_18 << 0x0);
    if (var_18 != 0x0) {
            _memr(var_8, var_C, var_18, var_30);
            var_C = var_C % 0x1000;
            if (var_C < 0x0) {
                    var_C = var_C + 0x1000;
            }
            if (sign_extend_64(var_C) + var_18 < 0x1001) {
                    __memcpy_chk(var_8 + sign_extend_64(var_C), var_20, var_18, 0xffffffffffffffff);
            }
            else {
                    __memcpy_chk(var_8 + sign_extend_64(var_C), var_20, sign_extend_64(0x1000 - var_C), 0xffffffffffffffff);
                    __memcpy_chk(var_8, var_20 + sign_extend_64(0x1000 - var_C), var_18 - sign_extend_64(0x1000 - var_C), 0xffffffffffffffff);
            }
            for (var_34 = 0x0; var_34 < var_18; var_34 = var_34 + 0x1) {
                    *(int32_t *)((var_C + var_34 & 0xfff) * 0x14 + var_8 + 0x1004) = *(int32_t *)var_28;
                    if (*(int32_t *)(var_8 + 0x15004) > 0x0) {
                            *(int32_t *)((var_C + var_34 & 0xfff) * 0x14 + var_8 + 0x1008) = 0x1;
                    }
                    _bout_mem_change(var_C + var_34 & 0xfff, var_28, *(int8_t *)(var_30 + var_34) & 0xff, *(int8_t *)(var_20 + var_34) & 0xff);
            }
            free(var_30);
    }
    return;
}

int _swap(int arg0, int arg1) {
    var_11 = *(int8_t *)arg0;
    *(int8_t *)arg0 = *(int8_t *)arg1;
    rax = var_11;
    *(int8_t *)arg1 = rax;
    return rax;
}

int _reverse_endian(int arg0, int arg1) {
    var_18 = arg0;
    var_1C = 0x0;
    var_20 = arg1 - 0x1;
    do {
            rax = var_1C;
            if (rax >= var_20) {
                break;
            }
            _swap(var_18 + sign_extend_64(var_1C));
            var_1C = var_1C + 0x1;
            var_20 = var_20 + 0xffffffff;
    } while (true);
    return rax;
}

int _memw_4(int arg0, int arg1, int arg2, int arg3) {
    _reverse_endian(var_10, 0x4);
    rax = _memw(arg0, arg1, 0x4, arg2, arg3);
    return rax;
}