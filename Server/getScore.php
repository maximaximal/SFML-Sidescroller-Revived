<?php
//This gets the wanted score from the csv databse
// Parameters: 
//		s = 1/0 - Activates the score-output
//		n = 1/0 - Activates the name-output
//		d = 1/0 - Activates the date-output
//		v = 1/0 - Activates the Version-Output (Float)
// Layout of the Output
//	
//	SCORE | NAME | DATE | VERSION
//     ---------------------------------------------------------
//	10000  | XYZ	  | Timestamp| Version
// Seperator: "|"

$handle = fopen("scores.csv", "r");
$File = fread($handle, filesize("scores.csv"));
fclose($handle);
$Entrys = explode("|", $File);
//Output Score
$i = 1;
foreach($Entrys as $Entry)
{
	$Entry = str_replace("\n", "", $Entry);
	$Values = explode(";", $Entry);
	if($Values[2] != "")
	{
		if($i < 100)
			echo " ";
		if($i < 10)
			echo " ";
		echo $i.". ";
		$i = $i + 1;
		$Score = $Values[0];
		$Author = $Values[1];
		$Time = $Values[2];
		$Version = $Values[3];
		if((int)$Score < 100000)
			echo " ";
		if((int)$Score < 10000)
			echo " ";
		if((int)$Score < 1000)
			echo " ";
		if((int)$Score < 100)
			echo " ";
		if((int)$Score < 10)
			echo " ";
		echo $Score;
		echo " ";
		echo date("d.m.y", $Time);
		echo " ";
		if($Version == "")
			$Version = "0.01";
		if($Author == "")
			$Author = "**Anonym**";
		echo "V".$Version;
		if($Version < 0)
		echo "     ";	
		if($Version < 0.1)
		echo "    ";
		if($Version < 0.01)
		echo "   ";	
		if($Version < 0.001)
		echo "  ";	
		if($Version < 0.0001)
		echo " ";
		echo "  ";
		echo " ";
		echo $Author;
		echo "\n";
	}
}
?>