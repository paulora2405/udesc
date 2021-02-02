struct param {
  int arg1;
  int arg2;
};

struct param2 {
	char nick[128];
	char content[1048576];
};

struct param3 {
	int cont_client_side;
	char nick_client_side[128];
};

struct return1 {
	int campo_vali;
	char content[1048576];
};

program PROG {
	version VERS {
		int			func1(void)		= 2;
		int			func2(param2)	= 3;
		return1 func4(param3) = 5;
	} = 1;
} = 0x30009999;
