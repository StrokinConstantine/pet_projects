
struct State
{
	int c; // c < 256 <-> out; c = 256 <-> c = split; c = 257 <-> c = Match
	State *out;
	State *out1;
	int lastlist;
}


