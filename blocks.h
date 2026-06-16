static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Interval*/	/*Signal*/
	{"CPU: ",	"top -bn1 | awk '/^%Cpu/ { printf \"%.0f%%\", 100-$8 }'",	5,		0},
	{"RAM: ",	"free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	10,		0},
	{"BAT: ",	"cat /sys/class/power_supply/BAT0/capacity | sed 's/$/%/'",	30,		0},
	{"BRI: ",	"/home/ms/.local/bin/brightness",				0,		11},
	{"VOL: ",	"/home/ms/.local/bin/volume",					1,		10},
	{"",		"date '+%a %d.%m  %H:%M'",					5,		0},
	{"PNG: ",	"ping -c10 -W2 artixlinux.org 2>/dev/null | awk -F'/' '/rtt/{print int($5)\"ms\"}' || echo '---'",	12,	0},
};
static char delim[] = " | ";
static unsigned int delimLen = 5;
