<?php

$json_str = file_get_contents('php://input');

$json_obj = json_decode($json_str, true);

$flag = file_get_contents('/flag');

if(!isset($json_obj["h"])){
	die(highlight_file(__file__));
}
if($json_obj["h"] == md5($flag)){
	echo "Woah, nice! <br>Flag: ".$flag;
}
else{
	echo "No luck :(";
}

