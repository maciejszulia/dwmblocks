static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Interval*/	/*Signal*/

	/* --- shown only while the pointer sits on the status --- */
	{"\004CLD \001",	"case ${BUTTON:-} in 1) notify-send 'Claude usage' \"$(/home/ms/.local/bin/cc-usage | tr -d '\\001-\\005')\" ;; esac; /home/ms/.local/bin/cc-usage",	30,	6},
	{"\004CDX \001",	"case ${BUTTON:-} in 1) notify-send 'Codex usage' \"$(/home/ms/.local/bin/codex-usage | tr -d '\\001-\\005')\" ;; esac; /home/ms/.local/bin/codex-usage",	60,	7},
	{"\004RAM \001",	"free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	10,		0},
	{"\004GPU \001",	"/home/ms/.local/bin/gpu",					5,		0},
	{"\004PNG\001",	"/home/ms/.local/bin/ping-artix",				2,		0},
	{"\004DSK \001",	"df -h / | awk 'NR==2{print $3\"/\"$2}'",		300,		0},
	{"\004BAT \001",	"case ${BUTTON:-} in 1) p=$(cat /sys/class/power_supply/BAT0/power_now 2>/dev/null || true); [ -n \"$p\" ] && p=$(awk -v p=\"$p\" 'BEGIN { printf \"%.2f W\", p / 1000000 }') || p=n/a; notify-send 'Battery' \"Status: $(cat /sys/class/power_supply/BAT0/status 2>/dev/null || echo unknown)\nCapacity: $(cat /sys/class/power_supply/BAT0/capacity 2>/dev/null || echo unknown)%\nPower draw: $p\" ;; esac; cap=$(cat /sys/class/power_supply/BAT0/capacity 2>/dev/null || echo 100); st=$(cat /sys/class/power_supply/BAT0/status 2>/dev/null || echo Charging); if [ \"$cap\" -le 20 ] && [ \"$st\" != \"Charging\" ]; then if [ $(( $(date +%s) % 2 )) -eq 0 ]; then printf '\\003%d%%\\001' \"$cap\"; else printf \"%d%%\" \"$cap\"; fi; else printf \"%d%%\" \"$cap\"; fi",	1,	8},

	/* ponytail: a block with no command is the \037 marker, i.e. the fold line */
	{"", NULL, 0, 0},

	/* --- always on the bar --- */
	/* ponytail: weather goes first. Its facts differ in length and a block shifts everything to
	 * its left, so here it moves no block that takes the wheel; CPU, VOL, BRI and the date keep
	 * their width (11.09: the fan floor and the volume swapped under the pointer). */
	{"",	"case ${BUTTON:-} in 1) /home/ms/.local/bin/weather --ack ;; 4) /home/ms/.local/bin/weather --turn 1 ;; 5) /home/ms/.local/bin/weather --turn -1 ;; 3) notify-send 'Weather forecast' \"$(/home/ms/.local/bin/weather --facts)\" ;; esac; /home/ms/.local/bin/weather",	1,	12},
	{"\004VPN \001",	"case ${BUTTON:-} in 1) if ip link show mvd >/dev/null 2>&1; then sudo -n wg-quick down mvd; else sudo -n wg-quick up mvd; fi >/dev/null 2>&1 ;; esac; if ip link show mvd >/dev/null 2>&1; then printf '\\005ON\\001'; else echo OFF; fi",	5,	13},
	{"\004CPU \001",	"/home/ms/.local/bin/cpu",					5,		14},
	{"\004VOL \001",	"/home/ms/.local/bin/volume",					1,		10},
	/* ponytail: BRI sits right of VOL so VOL grows leftwards into CPU; VOL/BRI print 4 columns so a
	 * mis-aimed wheel tick lands on the same block. CPU (signal 14) steps the fan floor,
	 * so the padding matters now. */
	{"\004BRI \001",	"/home/ms/.local/bin/brightness",				0,		11},
	{"",	"LC_TIME=pl_PL.utf8 date '+%a %d.%m %H:%M:%S'",			1,		0},
};
static char delim[] = "  ";
static unsigned int delimLen = 5;
