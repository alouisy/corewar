int _op_ldi(int arg0, int arg1) {
    var_10 = arg0;
    var_18 = arg1;
    var_19 = _memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x1);
    if (_check_pcb(var_19 & 0xff, 0xa) == 0x0) goto loc_100006f68;

loc_100006a89:
    rax = _type_from_pcb(var_19 & 0xff, 0x0);
    var_28 = _size_from_pt(rax, 0xa);
    rsi = rax - 0x1;
    COND = rsi == 0x0;
    var_4C = rax;
    if (COND) goto loc_100006ad1;

loc_100006abd:
    rax = var_4C - 0x2;
    COND = rax == 0x0;
    if (!COND) {
            var_2C = sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x2));
    }
    else {
            var_2C = _read_indirect(var_10, var_18, sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x2)));
    }
    goto loc_100006c18;

loc_100006c18:
    rax = _type_from_pcb(var_19 & 0xff, 0x1);
    var_34 = _size_from_pt(rax, 0xa);
    rax = rax - 0x1;
    COND = rax != 0x0;
    if (COND) goto loc_100006d54;

loc_100006c48:
    var_38 = sign_extend_64(_memr_1(var_10, var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_38) != 0x0) goto loc_100006d40;

loc_100006c7c:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xa);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xa) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007027;

loc_100007027:
    rax = var_4;
    return rax;

loc_100006d40:
    var_38 = _regr(var_18, var_38);
    goto loc_100006d72;

loc_100006d72:
    var_3C = sign_extend_64(_memr_1(var_10, var_34 + var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_3C) != 0x0) goto loc_100006e68;

loc_100006da4:
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0)) {
            rcx = *(int32_t *)(var_18 + 0xc);
            rax = _size_from_pcb(var_19 & 0xff, 0xa);
            _print_adv(var_10, var_18, rax + rcx + 0x2);
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xa) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007027;

loc_100006e68:
    var_40 = var_2C + var_38;
    var_44 = *(int32_t *)(var_18 + 0xc) + var_40 % 0x200;
    var_48 = _memr_4(var_10, var_44);
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
            printf("P% 5d | ldi %d %d r%d\n", *(int32_t *)(var_18 + 0x8), var_2C, var_38, var_3C);
    }
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0) {
                    printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", var_2C, var_38, var_40, var_44);
            }
    }
    _regw(var_18, var_3C, var_48);
    goto loc_100006f68;

loc_100006f68:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xa);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xa) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007027;

loc_100006d54:
    var_38 = sign_extend_64(_memr_2(var_10, var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    goto loc_100006d72;

loc_100006ad1:
    var_2C = sign_extend_64(_memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_2C) != 0x0) goto loc_100006ba9;

loc_100006afd:
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0)) {
            rcx = *(int32_t *)(var_18 + 0xc);
            rax = _size_from_pcb(var_19 & 0xff, 0xa);
            _print_adv(var_10, var_18, rax + rcx + 0x2);
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xa) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007027;

loc_100006ba9:
    var_2C = _regr(var_18, var_2C);
    goto loc_100006c18;
}
