<?php

$flag = file_get_contents('/flag');

if(!isset($_GET['h'])){
	die(highlight_file(__FILE__));
}

if($_GET['h'] == md5($_GET['h'])){
	echo 'Woah, you are PHP g0d: '.$flag;
}else{
	echo 'No luck';
}
