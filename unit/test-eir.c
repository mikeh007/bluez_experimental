/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2011  Intel Corporation
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/sdp.h>

#include "src/eir.h"

struct test_data {
	const void *eir_data;
	size_t eir_size;
	int flags;
	const char *name;
	gboolean name_complete;
};

static const unsigned char macbookair_data[] = {
		0x17, 0x09, 0x4d, 0x61, 0x72, 0x63, 0x65, 0x6c,
		0xe2, 0x80, 0x99, 0x73, 0x20, 0x4d, 0x61, 0x63,
		0x42, 0x6f, 0x6f, 0x6b, 0x20, 0x41, 0x69, 0x72,
		0x11, 0x03, 0x12, 0x11, 0x0c, 0x11, 0x0a, 0x11,
		0x1f, 0x11, 0x01, 0x11, 0x00, 0x10, 0x0a, 0x11,
		0x17, 0x11, 0x11, 0xff, 0x4c, 0x00, 0x01, 0x4d,
		0x61, 0x63, 0x42, 0x6f, 0x6f, 0x6b, 0x41, 0x69,
		0x72, 0x33, 0x2c, 0x31, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const struct test_data macbookair_test = {
	.eir_data = macbookair_data,
	.eir_size = sizeof(macbookair_data),
	.flags = -1,
	.name = "Marcel’s MacBook Air",
	.name_complete = TRUE,
};

static const unsigned char iphone5_data[] = {
		0x14, 0x09, 0x4d, 0x61, 0x72, 0x63, 0x65, 0x6c,
		0xe2, 0x80, 0x99, 0x73, 0x20, 0x69, 0x50, 0x68,
		0x6f, 0x6e, 0x65, 0x20, 0x35, 0x0f, 0x03, 0x00,
		0x12, 0x1f, 0x11, 0x2f, 0x11, 0x0a, 0x11, 0x0c,
		0x11, 0x16, 0x11, 0x32, 0x11, 0x01, 0x05, 0x11,
		0x07, 0xfe, 0xca, 0xca, 0xde, 0xaf, 0xde, 0xca,
		0xde, 0xde, 0xfa, 0xca, 0xde, 0x00, 0x00, 0x00,
		0x00, 0x27, 0xff, 0x00, 0x4c, 0x02, 0x24, 0x02,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const struct test_data iphone5_test = {
	.eir_data = iphone5_data,
	.eir_size = sizeof(iphone5_data),
	.flags = -1,
	.name = "Marcel’s iPhone 5",
	.name_complete = TRUE,
};

static const unsigned char ipadmini_data[] = {
		0x13, 0x09, 0x4d, 0x61, 0x72, 0x63, 0x65, 0x6c,
		0x27, 0x73, 0x20, 0x69, 0x50, 0x61, 0x64, 0x20,
		0x6d, 0x69, 0x6e, 0x69, 0x0b, 0x03, 0x00, 0x12,
		0x1f, 0x11, 0x0a, 0x11, 0x0c, 0x11, 0x32, 0x11,
		0x01, 0x05, 0x11, 0x07, 0xfe, 0xca, 0xca, 0xde,
		0xaf, 0xde, 0xca, 0xde, 0xde, 0xfa, 0xca, 0xde,
		0x00, 0x00, 0x00, 0x00, 0x27, 0xff, 0x00, 0x4c,
		0x02, 0x24, 0x02, 0x0c, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const struct test_data ipadmini_test = {
	.eir_data = ipadmini_data,
	.eir_size = sizeof(ipadmini_data),
	.flags = -1,
	.name = "Marcel's iPad mini",
	.name_complete = TRUE,
};

static const unsigned char fuelband_data[] = {
		0x0f, 0x09, 0x4e, 0x69, 0x6b, 0x65, 0x2b, 0x20,
		0x46, 0x75, 0x65, 0x6c, 0x42, 0x61, 0x6e, 0x64,
		0x11, 0x07, 0x00, 0x00, 0x00, 0x00, 0xde, 0xca,
		0xfa, 0xde, 0xde, 0xca, 0xde, 0xaf, 0xde, 0xca,
		0xca, 0xff, 0x02, 0x0a, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const struct test_data fuelband_test = {
	.eir_data = fuelband_data,
	.eir_size = sizeof(fuelband_data),
	.flags = -1,
	.name = "Nike+ FuelBand",
	.name_complete = TRUE,
};

static const unsigned char bluesc_data[] = {
		0x02, 0x01, 0x06, 0x03, 0x02, 0x16, 0x18, 0x12,
		0x09, 0x57, 0x61, 0x68, 0x6f, 0x6f, 0x20, 0x42,
		0x6c, 0x75, 0x65, 0x53, 0x43, 0x20, 0x76, 0x31,
		0x2e, 0x34,
};

static const struct test_data bluesc_test = {
	.eir_data = bluesc_data,
	.eir_size = sizeof(bluesc_data),
	.flags = 0x06,
	.name = "Wahoo BlueSC v1.4",
	.name_complete = TRUE,
};

static const unsigned char cookoo_data[] = {
		0x02, 0x01, 0x05, 0x05, 0x02, 0x02, 0x18, 0x0a,
		0x18, 0x0d, 0x09, 0x43, 0x4f, 0x4f, 0x4b, 0x4f,
		0x4f, 0x20, 0x77, 0x61, 0x74, 0x63, 0x68,
};

static const struct test_data cookoo_test = {
	.eir_data = cookoo_data,
	.eir_size = sizeof(cookoo_data),
	.flags = 0x05,
	.name = "COOKOO watch",
	.name_complete = TRUE,
};

static const unsigned char citizen_adv_data[] = {
		0x02, 0x01, 0x05, 0x05, 0x12, 0x7f, 0x01, 0x8f,
		0x01, 0x14, 0x09, 0x45, 0x63, 0x6f, 0x2d, 0x44,
		0x72, 0x69, 0x76, 0x65, 0x20, 0x50, 0x72, 0x6f,
		0x78, 0x69, 0x6d, 0x69, 0x74, 0x79,
};

static const struct test_data citizen_adv_test = {
	.eir_data = citizen_adv_data,
	.eir_size = sizeof(citizen_adv_data),
	.flags = 0x05,
	.name = "Eco-Drive Proximity",
	.name_complete = TRUE,
};

static const unsigned char citizen_scan_data[] = {
		0x02, 0x0a, 0x00, 0x11, 0x07, 0x1b, 0xc5, 0xd5,
		0xa5, 0x02, 0x00, 0x46, 0x9a, 0xe1, 0x11, 0xb7,
		0x8d, 0x60, 0xb4, 0x45, 0x2d,
};

static const struct test_data citizen_scan_test = {
	.eir_data = citizen_scan_data,
	.eir_size = sizeof(citizen_scan_data),
	.flags = -1,
};

static void test_basic(void)
{
	struct eir_data data;
	unsigned char buf[HCI_MAX_EIR_LENGTH];
	int err;

	memset(buf, 0, sizeof(buf));
	memset(&data, 0, sizeof(data));

	err = eir_parse(&data, buf, HCI_MAX_EIR_LENGTH);
	g_assert(err == 0);
	g_assert(data.services == NULL);
	g_assert(data.name == NULL);

	eir_data_free(&data);
}

static void test_parsing(gconstpointer data)
{
	const struct test_data *test = data;
	struct eir_data eir;
	int err;

	memset(&eir, 0, sizeof(eir));

	err = eir_parse(&eir, test->eir_data, test->eir_size);
	g_assert(err == 0);

	if (g_test_verbose() == TRUE)
		g_print("Flags: %d\n", eir.flags);

	if (g_test_verbose() == TRUE)
		g_print("Name: %s\n", eir.name);

	g_assert(eir.flags == test->flags);

	if (test->name) {
		g_assert(g_str_equal(eir.name, test->name) == TRUE);
		g_assert(eir.name_complete == test->name_complete);
	} else {
		g_assert(eir.name == NULL);
	}

	eir_data_free(&eir);
}

int main(int argc, char *argv[])
{
	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/eir/basic", test_basic);

	g_test_add_data_func("/eir/macbookair", &macbookair_test, test_parsing);
	g_test_add_data_func("/eir/iphone5", &iphone5_test, test_parsing);
	g_test_add_data_func("/eir/ipadmini", &ipadmini_test, test_parsing);
	g_test_add_data_func("/eir/fuelband", &fuelband_test, test_parsing);
	g_test_add_data_func("/ad/bluesc", &bluesc_test, test_parsing);
	g_test_add_data_func("/ad/cookoo", &cookoo_test, test_parsing);
	g_test_add_data_func("/ad/citizen1", &citizen_adv_test, test_parsing);
	g_test_add_data_func("/ad/citizen2", &citizen_scan_test, test_parsing);

	return g_test_run();
}
