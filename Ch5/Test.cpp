#include "Load"

int main(int argc, char *argv[])
{
	String a = CreateStringFromCharArray("Lorem ipsum dolor sit amet, consectetur adipiscing elit. An eum discere ea mavis, quae cum plane perdidiceriti nihil sciat? Princeps huius civitatis Phalereus Demetrius cum patria pulsus esset iniuria, ad Ptolomaeum se regem Alexandream contulit. Nunc dicam de voluptate, nihil scilicet novi, ea tamen, quae te ipsum probaturum esse confidam. Saepe ab Aristotele, a Theophrasto mirabiliter est laudata per se ipsa rerum scientia; Nos autem non solum beatae vitae istam esse oblectationem videmus, sed etiam levamentum miseriarum. Quodsi ipsam honestatem undique pertectam atque absolutam. Ut pulsi recurrant? Cuius ad naturam apta ratio vera illa et summa lex a philosophis dicitur. Duo Reges: constructio interrete. Tum ille: Ain tandem? Nam illud quidem adduci vix possum, ut ea, quae senserit ille, tibi non vera videantur. Quodsi, ne quo incommodo afficiare, non relinques amicum, tamen, ne sine fructu alligatus sis, ut moriatur optabis.");
	fmt::print("[OPERATION] Searching 'K' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "K");
	fmt::print("[OPERATION] Searching '123' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "123");
	fmt::print("[OPERATION] Searching '' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "");
	
	fmt::print("[OPERATION] Searching 'H' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "H");
	fmt::print("[OPERATION] Searching 'e' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "e");
	fmt::print("[OPERATION] Searching 'e' again...\n");
	BruteForcePatternMatchWithCharArray(a, "e");
	fmt::print("[OPERATION] Searching 'l' for the first time...\n");
	BruteForcePatternMatchWithCharArray(a, "l");
	fmt::print("[OPERATION] Size of string list: {}\n", Size(a) + 1);
	fmt::print("[OPERATION] String parts: \n");
	__StrPrintPart(a);
	
	fmt::print("[OPERATION] Searching 'l' again...\n");
	BruteForcePatternMatchWithCharArray(a, "l");
	fmt::print("[OPERATION] Size of string list: {}\n", Size(a) + 1);
	fmt::print("[OPERATION] String parts: \n");
	__StrPrintPart(a);
	
	fmt::print("[OPERATION] Searching 'l' again...\n");
	BruteForcePatternMatchWithCharArray(a, "l");
	BruteForcePatternMatchWithCharArray(a, "l0");
	BruteForcePatternMatchWithCharArray(a, "lo");
	BruteForcePatternMatchWithCharArray(a, "lo");

	String b = BruteForcePatternMatchWithCharArray(a, "lle");
	__StrPrint(b);
	return 0;
}