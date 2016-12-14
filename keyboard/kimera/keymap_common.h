/*
Copyright 2014 Kai Ryu <kai1103@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "keymap_in_eeprom.h"


extern const uint8_t keymaps[][MATRIX_SIZE];
extern const uint16_t fn_actions[];

/* 16 rows, 16 cols */
#define KEYMAP_16x16( \
    KAA, KAB, KAC, KAD, KAE, KAF, KAG, KAH, KAJ, KAK, KAL, KAM, KAN, KAP, KAQ, KAR, \
    KBA, KBB, KBC, KBD, KBE, KBF, KBG, KBH, KBJ, KBK, KBL, KBM, KBN, KBP, KBQ, KBR, \
    KCA, KCB, KCC, KCD, KCE, KCF, KCG, KCH, KCJ, KCK, KCL, KCM, KCN, KCP, KCQ, KCR, \
    KDA, KDB, KDC, KDD, KDE, KDF, KDG, KDH, KDJ, KDK, KDL, KDM, KDN, KDP, KDQ, KDR, \
    KEA, KEB, KEC, KED, KEE, KEF, KEG, KEH, KEJ, KEK, KEL, KEM, KEN, KEP, KEQ, KER, \
    KFA, KFB, KFC, KFD, KFE, KFF, KFG, KFH, KFJ, KFK, KFL, KFM, KFN, KFP, KFQ, KFR, \
    KGA, KGB, KGC, KGD, KGE, KGF, KGG, KGH, KGJ, KGK, KGL, KGM, KGN, KGP, KGQ, KGR, \
    KHA, KHB, KHC, KHD, KHE, KHF, KHG, KHH, KHJ, KHK, KHL, KHM, KHN, KHP, KHQ, KHR, \
    KJA, KJB, KJC, KJD, KJE, KJF, KJG, KJH, KJJ, KJK, KJL, KJM, KJN, KJP, KJQ, KJR, \
    KKA, KKB, KKC, KKD, KKE, KKF, KKG, KKH, KKJ, KKK, KKL, KKM, KKN, KKP, KKQ, KKR, \
    KLA, KLB, KLC, KLD, KLE, KLF, KLG, KLH, KLJ, KLK, KLL, KLM, KLN, KLP, KLQ, KLR, \
    KMA, KMB, KMC, KMD, KME, KMF, KMG, KMH, KMJ, KMK, KML, KMM, KMN, KMP, KMQ, KMR, \
    KNA, KNB, KNC, KND, KNE, KNF, KNG, KNH, KNJ, KNK, KNL, KNM, KNN, KNP, KNQ, KNR, \
    KPA, KPB, KPC, KPD, KPE, KPF, KPG, KPH, KPJ, KPK, KPL, KPM, KPN, KPP, KPQ, KPR, \
    KQA, KQB, KQC, KQD, KQE, KQF, KQG, KQH, KQJ, KQK, KQL, KQM, KQN, KQP, KQQ, KQR, \
    KRA, KRB, KRC, KRD, KRE, KRF, KRG, KRH, KRJ, KRK, KRL, KRM, KRN, KRP, KRQ, KRR  \
) { \
    KC_##KAA, KC_##KAB, KC_##KAC, KC_##KAD, KC_##KAE, KC_##KAF, KC_##KAG, KC_##KAH, KC_##KAJ, KC_##KAK, KC_##KAL, KC_##KAM, KC_##KAN, KC_##KAP, KC_##KAQ, KC_##KAR, \
    KC_##KBA, KC_##KBB, KC_##KBC, KC_##KBD, KC_##KBE, KC_##KBF, KC_##KBG, KC_##KBH, KC_##KBJ, KC_##KBK, KC_##KBL, KC_##KBM, KC_##KBN, KC_##KBP, KC_##KBQ, KC_##KBR, \
    KC_##KCA, KC_##KCB, KC_##KCC, KC_##KCD, KC_##KCE, KC_##KCF, KC_##KCG, KC_##KCH, KC_##KCJ, KC_##KCK, KC_##KCL, KC_##KCM, KC_##KCN, KC_##KCP, KC_##KCQ, KC_##KCR, \
    KC_##KDA, KC_##KDB, KC_##KDC, KC_##KDD, KC_##KDE, KC_##KDF, KC_##KDG, KC_##KDH, KC_##KDJ, KC_##KDK, KC_##KDL, KC_##KDM, KC_##KDN, KC_##KDP, KC_##KDQ, KC_##KDR, \
    KC_##KEA, KC_##KEB, KC_##KEC, KC_##KED, KC_##KEE, KC_##KEF, KC_##KEG, KC_##KEH, KC_##KEJ, KC_##KEK, KC_##KEL, KC_##KEM, KC_##KEN, KC_##KEP, KC_##KEQ, KC_##KER, \
    KC_##KFA, KC_##KFB, KC_##KFC, KC_##KFD, KC_##KFE, KC_##KFF, KC_##KFG, KC_##KFH, KC_##KFJ, KC_##KFK, KC_##KFL, KC_##KFM, KC_##KFN, KC_##KFP, KC_##KFQ, KC_##KFR, \
    KC_##KGA, KC_##KGB, KC_##KGC, KC_##KGD, KC_##KGE, KC_##KGF, KC_##KGG, KC_##KGH, KC_##KGJ, KC_##KGK, KC_##KGL, KC_##KGM, KC_##KGN, KC_##KGP, KC_##KGQ, KC_##KGR, \
    KC_##KHA, KC_##KHB, KC_##KHC, KC_##KHD, KC_##KHE, KC_##KHF, KC_##KHG, KC_##KHH, KC_##KHJ, KC_##KHK, KC_##KHL, KC_##KHM, KC_##KHN, KC_##KHP, KC_##KHQ, KC_##KHR, \
    KC_##KJA, KC_##KJB, KC_##KJC, KC_##KJD, KC_##KJE, KC_##KJF, KC_##KJG, KC_##KJH, KC_##KJJ, KC_##KJK, KC_##KJL, KC_##KJM, KC_##KJN, KC_##KJP, KC_##KJQ, KC_##KJR, \
    KC_##KKA, KC_##KKB, KC_##KKC, KC_##KKD, KC_##KKE, KC_##KKF, KC_##KKG, KC_##KKH, KC_##KKJ, KC_##KKK, KC_##KKL, KC_##KKM, KC_##KKN, KC_##KKP, KC_##KKQ, KC_##KKR, \
    KC_##KLA, KC_##KLB, KC_##KLC, KC_##KLD, KC_##KLE, KC_##KLF, KC_##KLG, KC_##KLH, KC_##KLJ, KC_##KLK, KC_##KLL, KC_##KLM, KC_##KLN, KC_##KLP, KC_##KLQ, KC_##KLR, \
    KC_##KMA, KC_##KMB, KC_##KMC, KC_##KMD, KC_##KME, KC_##KMF, KC_##KMG, KC_##KMH, KC_##KMJ, KC_##KMK, KC_##KML, KC_##KMM, KC_##KMN, KC_##KMP, KC_##KMQ, KC_##KMR, \
    KC_##KNA, KC_##KNB, KC_##KNC, KC_##KND, KC_##KNE, KC_##KNF, KC_##KNG, KC_##KNH, KC_##KNJ, KC_##KNK, KC_##KNL, KC_##KNM, KC_##KNN, KC_##KNP, KC_##KNQ, KC_##KNR, \
    KC_##KPA, KC_##KPB, KC_##KPC, KC_##KPD, KC_##KPE, KC_##KPF, KC_##KPG, KC_##KPH, KC_##KPJ, KC_##KPK, KC_##KPL, KC_##KPM, KC_##KPN, KC_##KPP, KC_##KPQ, KC_##KPR, \
    KC_##KQA, KC_##KQB, KC_##KQC, KC_##KQD, KC_##KQE, KC_##KQF, KC_##KQG, KC_##KQH, KC_##KQJ, KC_##KQK, KC_##KQL, KC_##KQM, KC_##KQN, KC_##KQP, KC_##KQQ, KC_##KQR, \
    KC_##KRA, KC_##KRB, KC_##KRC, KC_##KRD, KC_##KRE, KC_##KRF, KC_##KRG, KC_##KRH, KC_##KRJ, KC_##KRK, KC_##KRL, KC_##KRM, KC_##KRN, KC_##KRP, KC_##KRQ, KC_##KRR  \
}

/* 8 rows, 24 cols */
#define KEYMAP_8x24( \
    KAA, KAB, KAC, KAD, KAE, KAF, KAG, KAH, KAJ, KAK, KAL, KAM, KAN, KAP, KAQ, KAR, KAS, KAT, KAU, KAV, KAW, KAX, KAY, KAZ, \
    KBA, KBB, KBC, KBD, KBE, KBF, KBG, KBH, KBJ, KBK, KBL, KBM, KBN, KBP, KBQ, KBR, KBS, KBT, KBU, KBV, KBW, KBX, KBY, KBZ, \
    KCA, KCB, KCC, KCD, KCE, KCF, KCG, KCH, KCJ, KCK, KCL, KCM, KCN, KCP, KCQ, KCR, KCS, KCT, KCU, KCV, KCW, KCX, KCY, KCZ, \
    KDA, KDB, KDC, KDD, KDE, KDF, KDG, KDH, KDJ, KDK, KDL, KDM, KDN, KDP, KDQ, KDR, KDS, KDT, KDU, KDV, KDW, KDX, KDY, KDZ, \
    KEA, KEB, KEC, KED, KEE, KEF, KEG, KEH, KEJ, KEK, KEL, KEM, KEN, KEP, KEQ, KER, KES, KET, KEU, KEV, KEW, KEX, KEY, KEZ, \
    KFA, KFB, KFC, KFD, KFE, KFF, KFG, KFH, KFJ, KFK, KFL, KFM, KFN, KFP, KFQ, KFR, KFS, KFT, KFU, KFV, KFW, KFX, KFY, KFZ, \
    KGA, KGB, KGC, KGD, KGE, KGF, KGG, KGH, KGJ, KGK, KGL, KGM, KGN, KGP, KGQ, KGR, KGS, KGT, KGU, KGV, KGW, KGX, KGY, KGZ, \
    KHA, KHB, KHC, KHD, KHE, KHF, KHG, KHH, KHJ, KHK, KHL, KHM, KHN, KHP, KHQ, KHR, KHS, KHT, KHU, KHV, KHW, KHX, KHY, KHZ  \
) KEYMAP_16x16( \
    KAA, KAB, KAC, KAD, KAE, KAF, KAG, KAH, KAJ, KAK, KAL, KAM, KAN, KAP, KAQ, KAR, KAS, KAT, KAU, KAV, KAW, KAX, KAY, KAZ, \
    KBA, KBB, KBC, KBD, KBE, KBF, KBG, KBH, KBJ, KBK, KBL, KBM, KBN, KBP, KBQ, KBR, KBS, KBT, KBU, KBV, KBW, KBX, KBY, KBZ, \
    KCA, KCB, KCC, KCD, KCE, KCF, KCG, KCH, KCJ, KCK, KCL, KCM, KCN, KCP, KCQ, KCR, KCS, KCT, KCU, KCV, KCW, KCX, KCY, KCZ, \
    KDA, KDB, KDC, KDD, KDE, KDF, KDG, KDH, KDJ, KDK, KDL, KDM, KDN, KDP, KDQ, KDR, KDS, KDT, KDU, KDV, KDW, KDX, KDY, KDZ, \
    KEA, KEB, KEC, KED, KEE, KEF, KEG, KEH, KEJ, KEK, KEL, KEM, KEN, KEP, KEQ, KER, KES, KET, KEU, KEV, KEW, KEX, KEY, KEZ, \
    KFA, KFB, KFC, KFD, KFE, KFF, KFG, KFH, KFJ, KFK, KFL, KFM, KFN, KFP, KFQ, KFR, KFS, KFT, KFU, KFV, KFW, KFX, KFY, KFZ, \
    KGA, KGB, KGC, KGD, KGE, KGF, KGG, KGH, KGJ, KGK, KGL, KGM, KGN, KGP, KGQ, KGR, KGS, KGT, KGU, KGV, KGW, KGX, KGY, KGZ, \
    KHA, KHB, KHC, KHD, KHE, KHF, KHG, KHH, KHJ, KHK, KHL, KHM, KHN, KHP, KHQ, KHR, KHS, KHT, KHU, KHV, KHW, KHX, KHY, KHZ, \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO                                           \
)


/* 24 rows, 8 cols */
#define KEYMAP_24x8( \
    KAA, KAB, KAC, KAD, KAE, KAF, KAG, KAH, \
    KBA, KBB, KBC, KBD, KBE, KBF, KBG, KBH, \
    KCA, KCB, KCC, KCD, KCE, KCF, KCG, KCH, \
    KDA, KDB, KDC, KDD, KDE, KDF, KDG, KDH, \
    KEA, KEB, KEC, KED, KEE, KEF, KEG, KEH, \
    KFA, KFB, KFC, KFD, KFE, KFF, KFG, KFH, \
    KGA, KGB, KGC, KGD, KGE, KGF, KGG, KGH, \
    KHA, KHB, KHC, KHD, KHE, KHF, KHG, KHH, \
    KJA, KJB, KJC, KJD, KJE, KJF, KJG, KJH, \
    KKA, KKB, KKC, KKD, KKE, KKF, KKG, KKH, \
    KLA, KLB, KLC, KLD, KLE, KLF, KLG, KLH, \
    KMA, KMB, KMC, KMD, KME, KMF, KMG, KMH, \
    KNA, KNB, KNC, KND, KNE, KNF, KNG, KNH, \
    KPA, KPB, KPC, KPD, KPE, KPF, KPG, KPH, \
    KQA, KQB, KQC, KQD, KQE, KQF, KQG, KQH, \
    KRA, KRB, KRC, KRD, KRE, KRF, KRG, KRH, \
    KSA, KSB, KSC, KSD, KSE, KSF, KSG, KSH, \
    KTA, KTB, KTC, KTD, KTE, KTF, KTG, KTH, \
    KUA, KUB, KUC, KUD, KUE, KUF, KUG, KUH, \
    KVA, KVB, KVC, KVD, KVE, KVF, KVG, KVH, \
    KWA, KWB, KWC, KWD, KWE, KWF, KWG, KWH, \
    KXA, KXB, KXC, KXD, KXE, KXF, KXG, KXH, \
    KYA, KYB, KYC, KYD, KYE, KYF, KYG, KYH, \
    KZA, KZB, KZC, KZD, KZE, KZF, KZG, KZH  \
) KEYMAP_16x16( \
    KAA, KAB, KAC, KAD, KAE, KAF, KAG, KAH, \
    KBA, KBB, KBC, KBD, KBE, KBF, KBG, KBH, \
    KCA, KCB, KCC, KCD, KCE, KCF, KCG, KCH, \
    KDA, KDB, KDC, KDD, KDE, KDF, KDG, KDH, \
    KEA, KEB, KEC, KED, KEE, KEF, KEG, KEH, \
    KFA, KFB, KFC, KFD, KFE, KFF, KFG, KFH, \
    KGA, KGB, KGC, KGD, KGE, KGF, KGG, KGH, \
    KHA, KHB, KHC, KHD, KHE, KHF, KHG, KHH, \
    KJA, KJB, KJC, KJD, KJE, KJF, KJG, KJH, \
    KKA, KKB, KKC, KKD, KKE, KKF, KKG, KKH, \
    KLA, KLB, KLC, KLD, KLE, KLF, KLG, KLH, \
    KMA, KMB, KMC, KMD, KME, KMF, KMG, KMH, \
    KNA, KNB, KNC, KND, KNE, KNF, KNG, KNH, \
    KPA, KPB, KPC, KPD, KPE, KPF, KPG, KPH, \
    KQA, KQB, KQC, KQD, KQE, KQF, KQG, KQH, \
    KRA, KRB, KRC, KRD, KRE, KRF, KRG, KRH, \
    KSA, KSB, KSC, KSD, KSE, KSF, KSG, KSH, \
    KTA, KTB, KTC, KTD, KTE, KTF, KTG, KTH, \
    KUA, KUB, KUC, KUD, KUE, KUF, KUG, KUH, \
    KVA, KVB, KVC, KVD, KVE, KVF, KVG, KVH, \
    KWA, KWB, KWC, KWD, KWE, KWF, KWG, KWH, \
    KXA, KXB, KXC, KXD, KXE, KXF, KXG, KXH, \
    KYA, KYB, KYC, KYD, KYE, KYF, KYG, KYH, \
    KZA, KZB, KZC, KZD, KZE, KZF, KZG, KZH, \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO   \
)

/* ANSI 104 keymap */
#define KEYMAP_ANSI_104( \
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,   PRS, SCL, PAU,                       \
    GRV, _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9,  _0,  MNS, EQU, BSP,   INS, HOM, PGU,   NUM, PSL, PAS, PMN, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBR, RBR, BSL,   DEL, END, PGD,   P7,  P8,  P9,  PPL, \
    CAP, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCN, QUT,      ENT,                    P4,  P5,  P6,       \
    LSF, Z,   X,   C,   V,   B,   N,   M,   COM, DOT, SLS,           RSF,        UP,         P1,  P2,  P3,  PEN, \
    LCT, LGU, LAL,                SPC,                RAL, RGU, APP, RCT,   LFT, DOW, RGT,   P0,       PDT       \
) KEYMAP_8x24( \
    ESC, NO,  F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PRS, SCL, PAU, NO,  NO,  NO,  NO,  NO,  NO,  NO, \
    GRV, _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9,  _0,  MNS, EQU, BSP, INS, HOM, PGU, NUM, PSL, PAS, PMN, NO,  NO,  NO, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBR, RBR, BSL, DEL, END, PGD, P7,  P8,  P9,  PPL, NO,  NO,  NO, \
    CAP, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCN, QUT, NO,  ENT, NO,  NO,  NO,  P4,  P5,  P6,  NO,  NO,  NO,  NO, \
    LSF, Z,   X,   C,   V,   B,   N,   M,   COM, DOT, SLS, NO,  NO,  RSF, NO,  UP,  NO,  P1,  P2,  P3,  PEN, NO,  NO,  NO, \
    LCT, LGU, LAL, NO,  NO,  NO,  SPC, NO,  NO,  NO,  RAL, RGU, APP, RCT, LFT, DOW, RGT, P0,  NO,  PDT, NO,  NO,  NO,  NO, \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO  \
)

#endif
