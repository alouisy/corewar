int _op_lld(int arg0, int arg1) {
    var_8 = arg0;
    var_10 = arg1;
    var_11 = _memr_1(var_8, *(int32_t *)(var_10 + 0xc) + 0x1);
    if (_check_pcb(var_11 & 0xff, 0xd) != 0x0) {
            var_1C = _type_from_pcb(var_11 & 0xff, 0x0);
            var_20 = _size_from_pt(var_1C, 0xd);
            if (var_1C == 0x4) {
                    var_24 = _memr_4(var_8, *(int32_t *)(var_10 + 0xc) + 0x2);
            }
            else {
                    var_24 = sign_extend_64(_memr_2(var_8, *(int32_t *)(var_10 + 0xc) + sign_extend_64(_memr_2(var_8, *(int32_t *)(var_10 + 0xc) + 0x2))));
            }
            var_28 = sign_extend_64(_memr_1(var_8, var_20 + *(int32_t *)(var_10 + 0xc) + 0x2));
            if (_validate_regn(var_28) != 0x0) {
                    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
                            printf("P% 5d | lld %d r%d\n", *(int32_t *)(var_10 + 0x8), var_24, var_28);
                    }
                    rax = 0x1;
                    rdi = var_10;
                    if (var_24 != 0x0) {
                            rax = 0x0;
                    }
                    _carryw(rdi, rax);
                    _regw(var_10, var_28, var_24);
            }
    }
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_10 + 0xc);
                    rax = _size_from_pcb(var_11 & 0xff, 0xd);
                    _print_adv(var_8, var_10, rax + rcx + 0x2);
            }
    }
    rcx = *(int32_t *)(var_10 + 0xc);
    rax = _size_from_pcb(var_11 & 0xff, 0xd);
    rax = rax + rcx + 0x2;
    return rax;
}
