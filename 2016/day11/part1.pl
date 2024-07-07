use strict;
use warnings;
use Storable 'dclone';
use List::Util 'min';

my $initial_floor = 1;
my %items = (
    'PG' => 1, 'PM' => 1,
    'CG' => 2, 'CM' => 3,
    'CuG' => 2, 'CuM' => 3,
    'RuG' => 2, 'RuM' => 3,
    'PuG' => 2, 'PuM' => 3
);

sub bfs {
    my ($initial_floor, %initial_items) = @_;
    my @queue = ([$initial_floor, \%initial_items, 0]);
    my %visited;
    my $state = join('', $initial_floor, map { $_ . $initial_items{$_} } sort keys %initial_items);
    $visited{$state} = 1;

    while (@queue) {
        my ($floor, $items, $steps) = @{shift @queue};

        if (all_items_on_top($items)) {
            return $steps;
        }

        my @next_states = generate_next_states($floor, $items);
        for my $state (@next_states) {
            my ($next_floor, $next_items) = @$state;
            my $state_key = join('', $next_floor, map { $_ . $next_items->{$_} } sort keys %$next_items);
            next if $visited{$state_key};
            $visited{$state_key} = 1;
            push @queue, [$next_floor, $next_items, $steps + 1];
        }
    }
}

sub all_items_on_top {
    my ($items) = @_;
    for my $key (keys %$items) {
        return 0 if $items->{$key} != 4;
    }
    return 1;
}

sub generate_next_states {
    my ($floor, $items) = @_;
    my @next_states;
    my @directions = ($floor == 4 ? -1 : $floor == 1 ? 1 : (-1, 1));

    for my $dir (@directions) {
        my $next_floor = $floor + $dir;

        my @items_on_floor = grep { $items->{$_} == $floor } keys %$items;

        for my $i (0..$#items_on_floor) {
            for my $j ($i..$#items_on_floor) {
                my $new_items = dclone($items);
                $new_items->{$items_on_floor[$i]} = $next_floor;
                $new_items->{$items_on_floor[$j]} = $next_floor;
                push @next_states, [$next_floor, $new_items] if valid_state($new_items);
            }
        }
    }

    return @next_states;
}

sub valid_state {
    my ($items) = @_;
    my %chips;
    my %generators;

    for my $key (keys %$items) {
        if ($key =~ /M$/) {
            $chips{$items->{$key}}{$key} = 1;
        } else {
            $generators{$items->{$key}}{$key} = 1;
        }
    }

    for my $floor (keys %chips) {
        next unless exists $generators{$floor};
        for my $chip (keys %{$chips{$floor}}) {
            my $gen_key = $chip;
            $gen_key =~ s/M$/G/;
            next if exists $generators{$floor}{$gen_key};
            return 0;
        }
    }
    return 1;
}

my $steps = bfs($initial_floor, %items);
print "Minimum steps: $steps\n";
