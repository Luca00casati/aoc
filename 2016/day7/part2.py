def reverse(s):
    return s[1] + s[0] + s[1]

def check_aba(segments_outside, segments_inside):
    for segment_out in segments_outside:
        for i in range(len(segment_out) - 2):
            if segment_out[i] == segment_out[i+2] and segment_out[i] != segment_out[i+1]:
                aba = segment_out[i:i+3]
                bab = reverse(aba)
                for segment_in in segments_inside:
                    if bab in segment_in:
                        print("VALID")
                        return True
    print("INVALID")
    return False

nvalid = 0

with open("input.txt", 'r') as f:
    lines = f.readlines()

for line in lines:
    segments_outside = []
    segments_inside = []
    splitline = line.replace(']', ' ').replace('[', ' ').split()
    for index, part in enumerate(splitline):
        if index % 2 == 0:
            segments_outside.append(part)
        else:
            segments_inside.append(part)
    if check_aba(segments_outside, segments_inside):
        nvalid += 1

print(nvalid)