static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Interval*/	/*Signal*/

	/* --- shown only while the pointer sits on the status --- */
	{"\004CLD \001",	"/home/ms/.local/bin/cc-usage",					30,		0},
	{"\004CDX \001",	"/home/ms/.local/bin/codex-usage",				60,		0},
	{"\004CPU \001",	"top -bn1 | awk '/^%Cpu/ { printf \"%.0f%%\", 100-$8 }'",	5,		0},
	{"\004RAM \001",	"free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	10,		0},
	{"\004GPU \001",	"/home/ms/.local/bin/gpu",					5,		0},
	{"\004PNG\001",	"/home/ms/.local/bin/ping-artix",				2,		0},
	{"\004DSK \001",	"df -h / | awk 'NR==2{print $3\"/\"$2}'",		300,		0},
	{"\004BRI \001",	"/home/ms/.local/bin/brightness",				0,		11},

	/* ponytail: a block with no command is the \037 marker, i.e. the fold line */
	{"", NULL, 0, 0},

	/* --- always on the bar --- */
	{"\004BAT \001",	"cap=$(cat /sys/class/power_supply/BAT0/capacity 2>/dev/null || echo 100); st=$(cat /sys/class/power_supply/BAT0/status 2>/dev/null || echo Charging); if [ \"$cap\" -le 20 ] && [ \"$st\" != \"Charging\" ]; then if [ $(( $(date +%s) % 2 )) -eq 0 ]; then printf \"%c%d%%%c\" 3 \"$cap\" 1; else printf \"%d%%\" \"$cap\"; fi; else printf \"%d%%\" \"$cap\"; fi",	2,	0},
	{"\004VOL \001",	"/home/ms/.local/bin/volume",					1,		10},
	{"",	"/home/ms/.local/bin/weather",					1,		12},
	{"",	"LC_TIME=pl_PL.utf8 date '+%a %d.%m %H:%M'",			1,		0},
};
static char delim[] = "  ";
static unsigned int delimLen = 5;
