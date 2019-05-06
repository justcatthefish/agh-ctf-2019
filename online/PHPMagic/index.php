<?php

$flag = file_get_contents('/flag');

if(!isset($_GET['h'])){
	die(highlight_file(__FILE__));
}

if(md5($_GET['h']) == '0e123981239102931029314213338212'){
	echo 'Woah, you are PHP g0d: '.$flag;
}else{
	echo 'No luck';
}


