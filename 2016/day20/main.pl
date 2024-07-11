#!/usr/bin/perl
use strict;
use warnings;

if (@ARGV != 1) {
    die "Usage: $0 <blacklist_file>\n";
}

my $input_file = $ARGV[0];

open(my $fh, '<', $input_file) or die "Cannot open file $input_file: $!";

my @ranges;
while (my $line = <$fh>) {
    chomp $line;
    my ($start, $end) = split /-/, $line;
    push @ranges, [$start, $end];
}
close($fh);

@ranges = sort { $a->[0] <=> $b->[0] } @ranges;

my @merged_ranges;
foreach my $range (@ranges) {
    if (@merged_ranges && $merged_ranges[-1]->[1] >= $range->[0] - 1) {
        $merged_ranges[-1]->[1] = $range->[1] if $merged_ranges[-1]->[1] < $range->[1];
    } else {
        push @merged_ranges, $range;
    }
}

my $lowest_allowed_ip = undef;

my $total_ips = 4294967296; 
my $blocked_ips = 0;
my $last_end = -1;

foreach my $range (@merged_ranges) {
    if ($last_end + 1 <= $range->[0] - 1) {
        if (!defined $lowest_allowed_ip) {
            $lowest_allowed_ip = $last_end + 1;
        }
    }
    $blocked_ips += ($range->[1] - $range->[0] + 1);
    $last_end = $range->[1];
}

if ($last_end < 4294967295) {
    if (!defined $lowest_allowed_ip) {
        $lowest_allowed_ip = $last_end + 1;
    }
}

my $allowed_ips = $total_ips - $blocked_ips;

print "Lowest allowed IP: $lowest_allowed_ip\n";
print "Number of allowed IPs: $allowed_ips\n";
