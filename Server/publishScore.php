<?php

//Submits a score to the global scoreboard

if($_SERVER['HTTP_USER_AGENT'] == "libsfml-network/2.x")
{
	$handle = fopen("http://update.srcttp.org/SFML-Sidescroller/validate.php?md5=".$_GET['md5'], "r");
	$Valid = fread($handle, 10);
	fclose($handle);

	$handle = fopen("time_played", "r");
	$time_played_string = fread($handle, 1000);

	$timeplayed = intval($time_played_string);
	$timeplayed = $timeplayed + intval($_GET['time']);
	fclose($handle);
	if($timeplayed >= 1)
	{
		$handle = fopen("time_played", "w+");
		fwrite($handle, $timeplayed);
		fclose($handle);
	}
	if($Valid == "valid" && $timeplayed >= 1 && $_GET['v'] != "")
	{
		$newFileArray = array();
		$handle = fopen("scores.csv", "r");
		$File = fread($handle, filesize("scores.csv"));
		fclose($handle);
		$Entrys = explode("|", $File);
		$found = false;
		$i = 1;
		foreach($Entrys as $Entry)
		{
			$Entry = str_replace("\n", "", $Entry);
			$Values = explode(";", $Entry);
			if($Values[2] != "")
			{
				$Score = $Values[0];
				$Author = $Values[1];
				$Time = $Values[2];
				$Version = $Values[3];
				if($_GET['score'] > $Score && $found == false)
				{
					$found = true;
					$Line = $_GET['score'].";".$_GET['name'].";".time().";".$_GET['v'];
					$newFileArray[] = $Line;
					echo "You are # ".$i."\n";
				}
				$Line = $Score.";".$Author.";".$Time.";".$Version;
				$newFileArray[] = $Line;
				$i++;
			}
		}
		if(!$found)
			echo "You aren't in the top 500!\n";
		unlink("scores.csv");
		$handle = fopen("scores.csv", "a");
		$i = 1;
		foreach($newFileArray as $Line)
		{
			if($i > 500)
				continue;
			fputs($handle, $Line."|\n");
			$i++;
		}
		fclose($handle);
		echo "You've played ".$_GET['time']." seconds to reach ".$_GET['score']." points!\n";
		echo "SFML-Sidescroller has now been played for ".(int)($timeplayed / 60)." minutes!";
	}
	else
		echo "incorrect config!\n(hacker?!)";
}
else
	echo "You are not my game! You are a mean browser hacker ;)";
?>