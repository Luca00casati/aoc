#!/bin/bash

input="input.txt"

IFS=$'\n' read -d '' -r -a instructions < "$input"

declare -A registers
registers[a]=7 
registers[b]=0
registers[c]=0
registers[d]=0

get_value() {
    if [[ ${registers[$1]+_} ]]; then
        echo "${registers[$1]}"
    else
        echo "$1"
    fi
}

execute() {
    local i=0
    local instruction_count=${#instructions[@]}

    while (( i >= 0 && i < instruction_count )); do
        instruction="${instructions[$i]}"
        op="${instruction%% *}"
        args=(${instruction#* })
        
        case $op in
            cpy)
                src=$(get_value "${args[0]}")
                registers[${args[1]}]=$src
                ((i++))
                ;;
            inc)
                ((registers[${args[0]}]++))
                ((i++))
                ;;
            dec)
                ((registers[${args[0]}]--))
                ((i++))
                ;;
            jnz)
                x=$(get_value "${args[0]}")
                if (( x != 0 )); then
                    i=$((i + $(get_value "${args[1]}")))
                else
                    ((i++))
                fi
                ;;
            tgl)
                offset=$(get_value "${args[0]}")
                target_index=$((i + offset))
                if (( target_index >= 0 && target_index < instruction_count )); then
                    target_instruction="${instructions[$target_index]}"
                    target_op="${target_instruction%% *}"
                    target_args=(${target_instruction#* })

                    case $target_op in
                        cpy) new_op="jnz" ;;
                        inc) new_op="dec" ;;
                        dec) new_op="inc" ;;
                        jnz) new_op="cpy" ;;
                        tgl) new_op="inc" ;;
                        *) new_op="nop" ;;
                    esac

                    if [[ $new_op == "nop" ]]; then
                        instructions[$target_index]="${target_op} ${target_args[*]}"
                    else
                        instructions[$target_index]="$new_op ${target_args[*]}"
                    fi
                fi
                ((i++))
                ;;
            *)
                echo "Invalid operation $op"
                exit 1
                ;;
        esac
    done
}

execute

echo "${registers[a]}"
