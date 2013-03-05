<?php

function dopoly($x) {
	$pol = array_fill(0, 100, 0.0);
	$mu = 10.0;
	$s = 0.0;
	
	for ($j = 0; $j<100; $j++) {
		$mu = ($mu + 2.0) / 2.0;
		$pol[$j] = $mu;
	}
	
	for ($j=0; $j<100; $j++) {
	    $s = $x*$s + $pol[$j];
	}
	
	return $s;
}

$n = 100000;
$x = 0.2;
$pu = 0.0;

for($i=0; $i<$n; $i++) {
	$pu += dopoly($x);
}

print "PHP \n";
print $pu;