#include "Load"

int main(int argc, char *argv[])
{
	bool result = false;
	String a = CreateStringFromCharArray("Lorem ipsum dolor sit amet, consectetur adipiscing elit. An eum discere ea mavis, quae cum plane perdidiceriti nihil sciat? Princeps huius civitatis Phalereus Demetrius cum patria pulsus esset iniuria, ad Ptolomaeum se regem Alexandream contulit. Nunc dicam de voluptate, nihil scilicet novi, ea tamen, quae te ipsum probaturum esse confidam. Saepe ab Aristotele, a Theophrasto mirabiliter est laudata per se ipsa rerum scientia; Nos autem non solum beatae vitae istam esse oblectationem videmus, sed etiam levamentum miseriarum. Quodsi ipsam honestatem undique pertectam atque absolutam. Ut pulsi recurrant? Cuius ad naturam apta ratio vera illa et summa lex a philosophis dicitur. Duo Reges: constructio interrete. Tum ille: Ain tandem? Nam illud quidem adduci vix possum, ut ea, quae senserit ille, tibi non vera videantur. Quodsi, ne quo incommodo afficiare, non relinques amicum, tamen, ne sine fructu alligatus sis, ut moriatur optabis.");
	
	fmt::print("[OPERATION] Searching 'K' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "K") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Searching '123' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "123") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Searching '' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "") != NULL;
	fmt::print("{}\n", result);
	
	fmt::print("[OPERATION] Searching 'H' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "H") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Searching 'e' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "e") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Searching 'e' again...");
	result = KMPPatternMatchWithCharArray(a, "e") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Searching 'l' for the first time...");
	result = KMPPatternMatchWithCharArray(a, "l") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Size of string list: {}\n", Size(a) + 1);
	//fmt::print("[OPERATION] String parts: \n");
	//__StrPrintPart(a);
	
	fmt::print("[OPERATION] Searching 'l' again...");
	result = KMPPatternMatchWithCharArray(a, "l") != NULL;
	fmt::print("{}\n", result);
	fmt::print("[OPERATION] Size of string list: {}\n", Size(a) + 1);
	//fmt::print("[OPERATION] String parts: \n");
	//__StrPrintPart(a);
	
	fmt::print("[OPERATION] Searching 'l' again...");
	result = KMPPatternMatchWithCharArray(a, "l") != NULL;
	fmt::print("{}\n", result);
	
	String b = NULL;
	fmt::print("[OPERATION] Searching 'lle' for the first time...");
	result = (b = KMPPatternMatchWithCharArray(a, "lle")) != NULL;
	fmt::print("{}\n", result);
	__StrPrint(b);
	
	fmt::print("[OPERATION] Program finished.\n");
	return 0;
}