file(n) = sprintf("EffMap2d_%02dmm.txt",n)
str(n)  = sprintf("%d mm",n)

#set term postscript color
#set output "EffMap_40mm.eps"

do for[i=2:20]{
reset

set xlabel 'mm'
set ylabel 'mm'
set label str(i*5) at graph 0.9,0.80

set pm3d interpolate 2,2
set pm3d map
set palette define (0 'black',1 'navy',2 'dark-violet',3 'red',4 'yellow')

set xrange[-6:11]
set yrange[-10:10]

unset key

set cbrange[0:50]
set title 'Solid Angle (%)'
sp file(i*5) u 1:2:3 w pm3d

unset pm3d

#pause -1
pause 0.01
}
