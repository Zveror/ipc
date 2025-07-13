#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 		0
#define FAIL			1
#define QT_CMD_LN_PARAM	2
#define QT_OCTETS		4
#define CMD_LN_PARAM_IP	argv[1]

enum errors {
	CMD_LINE_PARAM_ERR	= 1,
	INCORRECT_IP_ERR	= 2
};

struct ip {
	unsigned char frst_octet;
	unsigned char scnd_octet;
	unsigned char thrd_octet;
	unsigned char frth_octet;
};

static struct ip *create_ip_struct_from_str(const char *ip_str, struct ip *ip_ptr);

int main(int argc, char **argv)
{
	struct ip *ip_ptr = malloc(sizeof(struct ip));
	if(argc != QT_CMD_LN_PARAM) {
		return CMD_LINE_PARAM_ERR;	
	}
	if(create_ip_struct_from_str(CMD_LN_PARAM_IP, ip_ptr)) {
		printf("%d.%d.%d.%d\n", ip_ptr->frst_octet, ip_ptr->scnd_octet, ip_ptr->thrd_octet, ip_ptr->frth_octet);
	}
	else {
		fputs("Error\n", stderr);
	}

	return SUCCESS;
}

static struct ip *create_ip_struct_from_str(const char *ip_str, struct ip *ip_ptr)
{
	unsigned int octet = 0;
	unsigned int dot_count = 0;
	unsigned int exists_num_in_oct = 0;

	for(int i = 0; ip_str[i] != '\0'; i++) {
		if(ip_str[i] >= '0' && ip_str[i] <= '9') {
			exists_num_in_oct = 1;
			octet = octet * 10 + (ip_str[i] - 48);
		}
		else if((ip_str[i] == '.') && (octet >= 0 && octet <= 255) && exists_num_in_oct) {
			dot_count++;
			switch(dot_count) {
				case 1:
					ip_ptr->frst_octet = octet;
					break;
				case 2:
					ip_ptr->scnd_octet = octet;
					break;
				case 3:
					ip_ptr->thrd_octet = octet;
					break;
				default:
					return NULL;
			}
			octet = 0;
			exists_num_in_oct = 0;
		}
		else {
			return NULL;
		}
	}
	if((dot_count == 3) && (octet >= 0 && octet <= 255) && exists_num_in_oct) {
		ip_ptr->frth_octet = octet;
	}
	else {
		return NULL;
	}
	return ip_ptr;
}
