int _op_live(int arg0, int arg1) {
    var_8 = arg0;
    var_10 = arg1;
    var_14 = _memr_4(var_8, *(int32_t *)(var_10 + 0xc) + 0x1);
    var_20 = _get_player(var_8, var_14);
    if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x4) != 0x0)) {
            printf("P% 5d | live %d\n", *(int32_t *)(var_10 + 0x8), var_14);
    }
    *(int32_t *)(var_10 + 0x5c) = *(int32_t *)(var_8 + 0x15004);
    *(int32_t *)(var_8 + 0x15014) = *(int32_t *)(var_8 + 0x15014) + 0x1;
    if (var_20 != 0x0) {
            if (((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) && ((*(int32_t *)(_options + 0x1c) & 0x1) != 0x0)) {
                    printf("Player %d (%s) is said to be alive\n", *(int32_t *)var_20, *(var_20 + 0x18) + 0x4);
            }
            *(int32_t *)(var_20 + 0x8) = *(int32_t *)(var_8 + 0x15004);
            *(int32_t *)(var_20 + 0x10) = *(int32_t *)(var_20 + 0x10) + 0x1;
            rax = sign_extend_64(*(int32_t *)var_20);
            *(int32_t *)(var_8 + rax * 0x4 + 0x15038) = *(int32_t *)(var_8 + rax * 0x4 + 0x15038) + 0x1;
            *(var_8 + 0x15030) = var_20;
            *(int32_t *)(sign_extend_64(*(int32_t *)(var_10 + 0xc)) * 0x14 + var_8 + 0x100c) = *(int32_t *)var_20;
            *(int32_t *)(sign_extend_64(*(int32_t *)(var_10 + 0xc)) * 0x14 + var_8 + 0x1010) = 0x1;
    }
    if (var_20 != 0x0) {
            var_2C = *(int32_t *)var_20;
    }
    else {
            var_2C = 0x0;
    }
    _bout_player_alive(var_2C, var_10);
    _bout_process_alive(var_10);
    if ((*(int32_t *)(_options + 0x4) == 0x0) && (*(int32_t *)_options == 0x0)) {
            if ((*(int32_t *)(_options + 0x1c) & 0x10) != 0x0) {
                    _print_adv(var_8, var_10, *(int32_t *)(var_10 + 0xc) + 0x5);
            }
    }
    rax = *(int32_t *)(var_10 + 0xc) + 0x5;
    return rax;
}
