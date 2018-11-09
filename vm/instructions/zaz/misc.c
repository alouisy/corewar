int _type_from_pcb(int arg0, int arg1) {
    var_D = SAR((arg0 & 0xff), 0x3 - arg1 << 0x1) & 0x3;
    if (sign_extend_64(var_D) == 0x2) {
            var_4 = 0x4;
    }
    else {
            if (sign_extend_64(var_D) == 0x3) {
                    var_4 = 0x2;
            }
            else {
                    if (sign_extend_64(var_D) == 0x1) {
                            var_4 = 0x1;
                    }
                    else {
                            var_4 = 0x0;
                    }
            }
    }
    rax = var_4;
    return rax;
}

int _size_from_pcb(int arg0, int arg1) {
    var_1 = arg0;
    var_8 = arg1;
    var_C = 0x0;
    var_10 = 0x0;
    while (var_C < *(int32_t *)(0x8 + _op_tab + sign_extend_64(var_8) * 0x38)) {
            var_10 = _size_from_pt(_type_from_pcb(var_1 & 0xff, var_C), var_8) + var_10;
            var_C = var_C + 0x1;
    }
    rax = var_10;
    return rax;
}
