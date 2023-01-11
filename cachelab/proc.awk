BEGIN {
	i = -1
	num = 0
	j = -1
}
{
	#print $0 >> "f0.output" 
	if (NR >= 6 && NR <= 133) {
		print $0
	}
	#if (NR >= 5) {
	#	j ++;
	#}
	#if ( i%4 == 3) {
	#	print "\n" >> "f0.output"
	#	num ++
	#}
	#if (j%16 == 15 && NR < 2053) {
	#	print "\n" >> "f0.output"
	#}
	#if (NR < 2053)
	#	print NR ") " $0
}
END {
	print "num is", num
}
