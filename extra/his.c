#include <stdio.h>
#define  SIZE   10
 
int main()
{
        int n[SIZE] = {19, 3, 15, 7, 11, 9, 13, 5, 17, 1};
        int i, j;
        
        printf("%s%13s%17s\n","Element/index", "Value", "Histogram");
        for(i=0; i <= (SIZE-1); i++)
        {
            printf("%9d%15d       ", i, n[i]);
            for(j = 1; j<= n[i]; j++)
                printf("*");
            printf("\n");
        }
        return   0;
}


/*

#Create a UDP agent and attach it to node n5
set udp5 [new Agent/UDP]
$ns attach-agent $n5 $udp5

# Create a CBR traffic source and attach it to udp5
set cbr5 [new Application/Traffic/CBR]
$cbr5 set packetSize_ 500
$cbr5 set interval_ 0.005
$cbr5 attach-agent $udp5

#Create a UDP agent and attach it to node n2
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2

# Create a CBR traffic source and attach it to udp1
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set interval_ 0.005
$cbr2 attach-agent $udp2


#Create a UDP agent and attach it to node n0
set udp3 [new Agent/UDP]
$ns attach-agent $n3 $udp3

# Create a CBR traffic source and attach it to udp3
set cbr3 [new Application/Traffic/CBR]
$cbr3 set packetSize_ 500
$cbr3 set interval_ 0.005
$cbr3 attach-agent $udp3

#Create a UDP agent and attach it to node n4
set udp4 [new Agent/UDP]
$ns attach-agent $n4 $udp4

# Create a CBR traffic source and attach it to udp4
set cbr4 [new Application/Traffic/CBR]
$cbr4 set packetSize_ 500
$cbr4 set interval_ 0.005
$cbr4 attach-agent $udp4

*/