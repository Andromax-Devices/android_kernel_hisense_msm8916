#! /usr/bin/perl

my $board_name;
my $console;

open CONFIG, "<./kout/.config" or die "Open .config file error";
while(<CONFIG>)
{
    if (/CONFIG_PRODUCT_INFO\s*=\s*\"(\w+)\"/)
    {
        $board_name = $1;
        next;
    }
    
    if (/console=(\w+),/)
    {
        $console = $1;
        next;
    }
        
    if ($board_name ne "" && $console ne "")
    {
        last;
    }
}
close (CONFIG);

open OUT, "> board_info.txt" or die "open board_info.txt file error!";
print OUT $board_name." ".$console;
close (OUT);
