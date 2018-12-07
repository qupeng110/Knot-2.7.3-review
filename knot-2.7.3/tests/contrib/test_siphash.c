/*  Copyright (C) 2018 CZ.NIC, z.s.p.o. <knot-dns@labs.nic.cz>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <tap/basic.h>

// Prevent possible linking with a system SiphHash (OpenBSD).
#include "contrib/openbsd/siphash.c"

// https://github.com/veorq/SipHash
const uint8_t vectors24[64][8] = {
	{ 0x31, 0x0e, 0x0e, 0xdd, 0x47, 0xdb, 0x6f, 0x72 },
	{ 0xfd, 0x67, 0xdc, 0x93, 0xc5, 0x39, 0xf8, 0x74 },
	{ 0x5a, 0x4f, 0xa9, 0xd9, 0x09, 0x80, 0x6c, 0x0d },
	{ 0x2d, 0x7e, 0xfb, 0xd7, 0x96, 0x66, 0x67, 0x85 },
	{ 0xb7, 0x87, 0x71, 0x27, 0xe0, 0x94, 0x27, 0xcf },
	{ 0x8d, 0xa6, 0x99, 0xcd, 0x64, 0x55, 0x76, 0x18 },
	{ 0xce, 0xe3, 0xfe, 0x58, 0x6e, 0x46, 0xc9, 0xcb },
	{ 0x37, 0xd1, 0x01, 0x8b, 0xf5, 0x00, 0x02, 0xab },
	{ 0x62, 0x24, 0x93, 0x9a, 0x79, 0xf5, 0xf5, 0x93 },
	{ 0xb0, 0xe4, 0xa9, 0x0b, 0xdf, 0x82, 0x00, 0x9e },
	{ 0xf3, 0xb9, 0xdd, 0x94, 0xc5, 0xbb, 0x5d, 0x7a },
	{ 0xa7, 0xad, 0x6b, 0x22, 0x46, 0x2f, 0xb3, 0xf4 },
	{ 0xfb, 0xe5, 0x0e, 0x86, 0xbc, 0x8f, 0x1e, 0x75 },
	{ 0x90, 0x3d, 0x84, 0xc0, 0x27, 0x56, 0xea, 0x14 },
	{ 0xee, 0xf2, 0x7a, 0x8e, 0x90, 0xca, 0x23, 0xf7 },
	{ 0xe5, 0x45, 0xbe, 0x49, 0x61, 0xca, 0x29, 0xa1 },
	{ 0xdb, 0x9b, 0xc2, 0x57, 0x7f, 0xcc, 0x2a, 0x3f },
	{ 0x94, 0x47, 0xbe, 0x2c, 0xf5, 0xe9, 0x9a, 0x69 },
	{ 0x9c, 0xd3, 0x8d, 0x96, 0xf0, 0xb3, 0xc1, 0x4b },
	{ 0xbd, 0x61, 0x79, 0xa7, 0x1d, 0xc9, 0x6d, 0xbb },
	{ 0x98, 0xee, 0xa2, 0x1a, 0xf2, 0x5c, 0xd6, 0xbe },
	{ 0xc7, 0x67, 0x3b, 0x2e, 0xb0, 0xcb, 0xf2, 0xd0 },
	{ 0x88, 0x3e, 0xa3, 0xe3, 0x95, 0x67, 0x53, 0x93 },
	{ 0xc8, 0xce, 0x5c, 0xcd, 0x8c, 0x03, 0x0c, 0xa8 },
	{ 0x94, 0xaf, 0x49, 0xf6, 0xc6, 0x50, 0xad, 0xb8 },
	{ 0xea, 0xb8, 0x85, 0x8a, 0xde, 0x92, 0xe1, 0xbc },
	{ 0xf3, 0x15, 0xbb, 0x5b, 0xb8, 0x35, 0xd8, 0x17 },
	{ 0xad, 0xcf, 0x6b, 0x07, 0x63, 0x61, 0x2e, 0x2f },
	{ 0xa5, 0xc9, 0x1d, 0xa7, 0xac, 0xaa, 0x4d, 0xde },
	{ 0x71, 0x65, 0x95, 0x87, 0x66, 0x50, 0xa2, 0xa6 },
	{ 0x28, 0xef, 0x49, 0x5c, 0x53, 0xa3, 0x87, 0xad },
	{ 0x42, 0xc3, 0x41, 0xd8, 0xfa, 0x92, 0xd8, 0x32 },
	{ 0xce, 0x7c, 0xf2, 0x72, 0x2f, 0x51, 0x27, 0x71 },
	{ 0xe3, 0x78, 0x59, 0xf9, 0x46, 0x23, 0xf3, 0xa7 },
	{ 0x38, 0x12, 0x05, 0xbb, 0x1a, 0xb0, 0xe0, 0x12 },
	{ 0xae, 0x97, 0xa1, 0x0f, 0xd4, 0x34, 0xe0, 0x15 },
	{ 0xb4, 0xa3, 0x15, 0x08, 0xbe, 0xff, 0x4d, 0x31 },
	{ 0x81, 0x39, 0x62, 0x29, 0xf0, 0x90, 0x79, 0x02 },
	{ 0x4d, 0x0c, 0xf4, 0x9e, 0xe5, 0xd4, 0xdc, 0xca },
	{ 0x5c, 0x73, 0x33, 0x6a, 0x76, 0xd8, 0xbf, 0x9a },
	{ 0xd0, 0xa7, 0x04, 0x53, 0x6b, 0xa9, 0x3e, 0x0e },
	{ 0x92, 0x59, 0x58, 0xfc, 0xd6, 0x42, 0x0c, 0xad },
	{ 0xa9, 0x15, 0xc2, 0x9b, 0xc8, 0x06, 0x73, 0x18 },
	{ 0x95, 0x2b, 0x79, 0xf3, 0xbc, 0x0a, 0xa6, 0xd4 },
	{ 0xf2, 0x1d, 0xf2, 0xe4, 0x1d, 0x45, 0x35, 0xf9 },
	{ 0x87, 0x57, 0x75, 0x19, 0x04, 0x8f, 0x53, 0xa9 },
	{ 0x10, 0xa5, 0x6c, 0xf5, 0xdf, 0xcd, 0x9a, 0xdb },
	{ 0xeb, 0x75, 0x09, 0x5c, 0xcd, 0x98, 0x6c, 0xd0 },
	{ 0x51, 0xa9, 0xcb, 0x9e, 0xcb, 0xa3, 0x12, 0xe6 },
	{ 0x96, 0xaf, 0xad, 0xfc, 0x2c, 0xe6, 0x66, 0xc7 },
	{ 0x72, 0xfe, 0x52, 0x97, 0x5a, 0x43, 0x64, 0xee },
	{ 0x5a, 0x16, 0x45, 0xb2, 0x76, 0xd5, 0x92, 0xa1 },
	{ 0xb2, 0x74, 0xcb, 0x8e, 0xbf, 0x87, 0x87, 0x0a },
	{ 0x6f, 0x9b, 0xb4, 0x20, 0x3d, 0xe7, 0xb3, 0x81 },
	{ 0xea, 0xec, 0xb2, 0xa3, 0x0b, 0x22, 0xa8, 0x7f },
	{ 0x99, 0x24, 0xa4, 0x3c, 0xc1, 0x31, 0x57, 0x24 },
	{ 0xbd, 0x83, 0x8d, 0x3a, 0xaf, 0xbf, 0x8d, 0xb7 },
	{ 0x0b, 0x1a, 0x2a, 0x32, 0x65, 0xd5, 0x1a, 0xea },
	{ 0x13, 0x50, 0x79, 0xa3, 0x23, 0x1c, 0xe6, 0x60 },
	{ 0x93, 0x2b, 0x28, 0x46, 0xe4, 0xd7, 0x06, 0x66 },
	{ 0xe1, 0x91, 0x5f, 0x5c, 0xb1, 0xec, 0xa4, 0x6c },
	{ 0xf3, 0x25, 0x96, 0x5c, 0xa1, 0x6d, 0x62, 0x9f },
	{ 0x57, 0x5f, 0xf2, 0x8e, 0x60, 0x38, 0x1b, 0xe5 },
	{ 0x72, 0x45, 0x06, 0xeb, 0x4c, 0x32, 0x8a, 0x95 },
};

static void block_test(SIPHASH_KEY *key, uint8_t *data, int data_len, int block_len)
{
	int count = data_len / block_len;
	int rest = data_len % block_len;

	SIPHASH_CTX ctx;
	SipHash24_Init(&ctx, key);

	for (int i = 0; i < count; i++) {
		SipHash24_Update(&ctx, data + i * block_len, block_len);
	}
	SipHash24_Update(&ctx, data + count * block_len, rest);

	uint64_t hash = SipHash24_End(&ctx);
	ok(memcmp(&hash, vectors24[data_len], sizeof(uint64_t)) == 0,
	   "siphash24: %i-byte block updates", block_len);
}

int main(void)
{
	plan_lazy();

	SIPHASH_KEY key;
	memcpy(&key.k0, "\x00\x01\x02\x03\x04\x05\x06\x07", sizeof(uint64_t));
	memcpy(&key.k1, "\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f", sizeof(uint64_t));

	uint8_t data[64];
	for (int i = 0; i < sizeof(data); i++) {
		data[i] = i;
	}

	for (int data_len = 0; data_len < sizeof(data); data_len++) {
		diag("data length %i", data_len);

		uint64_t hash = SipHash24(&key, data, data_len);
		ok(memcmp(&hash, vectors24[data_len], sizeof(uint64_t)) == 0,
		   "siphash24: 1-block update");

		for (int block_len = 1; block_len <= 8; block_len++) {
			block_test(&key, data, data_len, block_len);
		}
	}

	return 0;
}
