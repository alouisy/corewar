int _op_sti(int arg0, int arg1) {
    var_10 = arg0;
    var_18 = arg1;
    var_19 = _memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x1);
    if (_check_pcb(var_19 & 0xff, 0xb) == 0x0) goto loc_100007572;

loc_100007089:
    var_24 = sign_extend_64(_memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_24) != 0x0) goto loc_100007168;

loc_1000070bc:
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0)) {
            rcx = *(int32_t *)(var_18 + 0xc);
            rax = _size_from_pcb(var_19 & 0xff, 0xb);
            _print_adv(var_10, var_18, rax + rcx + 0x2);
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xb) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007631;

loc_100007631:
    rax = var_4;
    return rax;

loc_100007168:
    rax = _type_from_pcb(var_19 & 0xff, 0x1);
    var_30 = _size_from_pt(rax, 0xb);
    rsi = rax - 0x1;
    COND = rsi == 0x0;
    var_64 = rax;
    if (COND) goto loc_1000071b3;

loc_10000719a:
    rax = var_64 - 0x2;
    COND = rax == 0x0;
    if (!COND) {
            var_34 = sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x3));
    }
    else {
            var_34 = _read_indirect(var_10, var_18, sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x3)));
    }
    goto loc_10000731b;

loc_10000731b:
    rax = _type_from_pcb(var_19 & 0xff, 0x2);
    rax = rax - 0x1;
    COND = rax != 0x0;
    if (COND) goto loc_10000744a;

loc_10000733b:
    rax = sub_100007340();
    return rax;

loc_10000744a:
    var_3C = sign_extend_64(_memr_2(var_10, var_30 + *(int32_t *)(var_18 + 0xc) + 0x3));
    var_40 = var_34 + var_3C;
    var_44 = *(int32_t *)(var_18 + 0xc) + var_40 % 0x200;
    var_48 = _regr(var_18, var_24);
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
            printf("P% 5d | sti r%d %d %d\n", *(int32_t *)(var_18 + 0x8), var_24, var_34, var_3C);
    }
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0) {
                    printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", var_34, var_3C, var_40, var_44);
            }
    }
    _memw_4(var_10, var_44, var_48, *var_18);
    goto loc_100007572;

loc_100007572:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xb);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xb) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007631;

loc_1000071b3:
    var_34 = sign_extend_64(_memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x3));
    if (_validate_regn(var_34) != 0x0) goto loc_10000729a;

loc_1000071e2:
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0)) {
            rcx = *(int32_t *)(var_18 + 0xc);
            rax = _size_from_pcb(var_19 & 0xff, 0xb);
            _print_adv(var_10, var_18, rax + rcx + 0x2);
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xb) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007631;

loc_10000729a:
    var_34 = _regr(var_18, var_34);
    goto loc_10000731b;
}