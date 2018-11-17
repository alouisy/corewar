int _op_lldi(int arg0, int arg1) {
    var_10 = arg0;
    var_18 = arg1;
    var_19 = _memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x1);
    if (_check_pcb(var_19 & 0xff, 0xe) == 0x0) goto loc_100007ea9;

loc_1000079c9:
    rax = _type_from_pcb(var_19 & 0xff, 0x0);
    var_28 = _size_from_pt(rax, 0xe);
    rsi = rax - 0x1;
    COND = rsi == 0x0;
    var_4C = rax;
    if (COND) goto loc_100007a11;

loc_1000079fd:
    rax = var_4C - 0x2;
    COND = rax == 0x0;
    if (!COND) {
            var_2C = sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x2));
    }
    else {
            var_2C = _read_indirect(var_10, var_18, sign_extend_64(_memr_2(var_10, *(int32_t *)(var_18 + 0xc) + 0x2)));
    }
    goto loc_100007b58;

loc_100007b58:
    rax = _type_from_pcb(var_19 & 0xff, 0x1);
    var_34 = _size_from_pt(rax, 0xe);
    rax = rax - 0x1;
    COND = rax != 0x0;
    if (COND) goto loc_100007c94;

loc_100007b88:
    var_38 = sign_extend_64(_memr_1(var_10, var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_38) != 0x0) goto loc_100007c80;

loc_100007bbc:
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0)) {
            rcx = *(int32_t *)(var_18 + 0xc);
            rax = _size_from_pcb(var_19 & 0xff, 0xe);
            _print_adv(var_10, var_18, rax + rcx + 0x2);
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xe) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007f68;

loc_100007f68:
    rax = var_4;
    return rax;

loc_100007c80:
    var_38 = _regr(var_18, var_38);
    goto loc_100007cb2;

loc_100007cb2:
    var_3C = sign_extend_64(_memr_1(var_10, var_34 + var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_3C) != 0x0) goto loc_100007da8;

loc_100007ce4:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xe);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xe) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007f68;

loc_100007da8:
    var_40 = var_2C + var_38;
    var_44 = *(int32_t *)(var_18 + 0xc) + var_40;
    var_48 = _memr_4(var_10, var_44);
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
            printf("P% 5d | lldi %d %d r%d\n", *(int32_t *)(var_18 + 0x8), var_2C, var_38, var_3C);
    }
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
            printf("       | -> load from %d + %d = %d (with pc %d)\n", var_2C, var_38, var_40, var_44);
    }
    rax = 0x1;
    rdi = var_18;
    if (var_48 != 0x0) {
            rax = 0x0;
    }
    _carryw(rdi, rax);
    _regw(var_18, var_3C, var_48);
    goto loc_100007ea9;

loc_100007ea9:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xe);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xe) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007f68;

loc_100007c94:
    var_38 = sign_extend_64(_memr_2(var_10, var_28 + *(int32_t *)(var_18 + 0xc) + 0x2));
    goto loc_100007cb2;

loc_100007a11:
    var_2C = sign_extend_64(_memr_1(var_10, *(int32_t *)(var_18 + 0xc) + 0x2));
    if (_validate_regn(var_2C) != 0x0) goto loc_100007ae9;

loc_100007a3d:
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    rcx = *(int32_t *)(var_18 + 0xc);
                    rax = _size_from_pcb(var_19 & 0xff, 0xe);
                    _print_adv(var_10, var_18, rax + rcx + 0x2);
            }
    }
    var_4 = _size_from_pcb(var_19 & 0xff, 0xe) + *(int32_t *)(var_18 + 0xc) + 0x2;
    goto loc_100007f68;

loc_100007ae9:
    var_2C = _regr(var_18, var_2C);
    goto loc_100007b58;
}
