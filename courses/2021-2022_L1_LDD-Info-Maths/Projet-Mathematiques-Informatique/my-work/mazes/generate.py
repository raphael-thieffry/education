from labyrinthe import labyrinthe
import sys
import os
from color import Color

        
def help(): 
    print(f"{Color.red}Usage: py {sys.argv[0]} [options]{Color.end}")
    print(f"Options:")
    print(f"\t--geometry <width>x<height> : size of the labyrinthe (default : 10x10)")
    print(f"\t--output -o <output>        : output filename (default : labyrinthe)")
    print(f"\t--resolve                   : resolve the labyrinthe in a gif animation")
    print(f"\t--help -h                   : show this help{Color.end}")
    return

def next_arg(argv, arg):
    for i in range(len(argv)):
        if argv[i] == arg:
            try:
                return str(argv[i+1])
            except:
                print(f"{Color.red}Error : {arg} must be followed by a value{Color.end}")
                help()
                sys.exit(1)
    return None


def write_file_pgm(filename,j, T):
    os.system("mkdir -p img")
    with open(f"img/{filename}_{j+1:04}.pgm", 'w') as f:
            f.write('P3\n')
            f.write(f'{2*w+1} {2*h+1}\n')
            f.write('255\n')
            for line in T:
                for c in line:
                    if c == 0:    
                        f.write(f'255 255 255 ')
                    elif c == 1:
                        f.write(f'0 0 0 ')
                    elif c == 2:
                        f.write(f'255 0 0 ')
                f.write('\n')

def write_file_pbm(filename, T):
    os.system("mkdir -p img")
    with open(f"img/{filename}.pbm", 'w') as f:
            f.write('P1\n')
            f.write(f'{2*w+1} {2*h+1}\n')
            for line in T:
                for c in line:
                    f.write(f'{c} ')
                f.write('\n')



def to_gif(l: labyrinthe, r : list, filename: str):
    """
    Convert labyrinthe solution to a gif
    """
    base = l.base
    global w, h
    T = []
    for y in range(2*h+1):
        L = []
        for x in range(2*w+1):
            if(y == 0 or x == 0 or x == 2*w or y == 2*h or x%2==0 or y%2==0):
                L.append(1)
            else:
                L.append(0)
        T.append(L)
    
    T[l.start[1]*2+1][0] = 0
    T[2*l.end[1]-1][2*w] = 0

    for line in base:
        for c in line:
            if not c.droite:
                T[2*(c.y - 1) + 1][2*c.x] = 0
            if not c.bas:
                T[2*c.y][2*(c.x - 1) +1] = 0

    j = 1

    write_file_pgm(filename, j, T)
    T[l.start[1]*2+1][0] = 2
    j += 1
    write_file_pgm(filename, j, T)



    for i in range(len(r) - 1):
        c = r[i]
        c_n = r[i + 1]
        if c_n[0] > c[0]:
            T[2*(c[1]) + 1][2*c[0] + 2] = 2
        
        elif c_n[0] < c[0]:
            T[2*(c[1]) + 1][2*c[0]] = 2
        elif c_n[1] > c[1]:
            T[2*(c[1]) + 2][2*c[0]+1] = 2
        elif c_n[1] < c[1]:
            T[2*(c[1])][2*c[0]+1] = 2
        

        T[2*(c[1]) + 1][2*c[0] + 1] = 2
        j+=1
        write_file_pgm(filename, j, T)

    j+=1

    T[2*l.end[1]-1][2*w] = 2
    T[2*l.end[1]-1][2*w-1] = 2
    write_file_pgm(filename, j, T)

def to_pbm_picture(l: labyrinthe, filename: str):
    """
    Convert a labyrinthe to a PBM picture
    """
    base = l.base
    global w, h
    T = []
    for y in range(2*h+1):
        L = []
        for x in range(2*w+1):
            if(y == 0 or x == 0 or x == 2*w or y == 2*h or x%2==0 or y%2==0):
                L.append(1)
            else:
                L.append(0)
        T.append(L)
    T[l.start[1]*2+1][0] = 0
    T[2*l.end[1]-1][2*w] = 0

    for line in base:
        for c in line:
            if not c.droite:
                T[2*(c.y - 1) + 1][2*c.x] = 0
            if not c.bas:
                T[2*c.y][2*(c.x - 1) +1] = 0

    write_file_pbm(filename, T)


def main(out, w = 10, h = 10, resolve=False):
    print(f"{Color.orange}Generating a labyrinthe (size : w = {Color.red}{w}{Color.orange}, h = {Color.red}{h}{Color.orange})... {Color.end}", end="", flush=True)
    l = labyrinthe(w, h)
    l.generate()
    print(f"{Color.green}OK {Color.end}")
    

    print(f"{Color.blue}Converting labyrinthe to png... {Color.end}", end="", flush=True)
    to_pbm_picture(l, out)
    if w > 50 or h > 50:
        os.system(f"convert -scale {2*max(w, h)+1} img/{out}.pbm {out}.png")
    else:
        os.system(f"convert -scale {2*max(w, h)*10+1} img/{out}.pbm {out}.png")
    print(f"{Color.green}Success !{Color.end}")
    os.system(f"rm img/*.pbm")

    print(f"{Color.blue}Filename : {Color.red}{out}.png{Color.end}")

    if resolve:
        print(f"{Color.orange}Resolving the labyrinthe... {Color.end}", end="", flush=True)
        r = l.solution()
        print(f"{Color.green}OK {Color.end}")
        print(f"{Color.blue}Creating the animation of the solution... {Color.end}", end="", flush=True)
        to_gif(l, r, out)
        if w > 30 or h > 30:
            os.system(f"convert -scale {2*max(w, h)+1} -delay 10 img/*.pgm {out}_solution.gif")
        else:
            os.system(f"convert -scale {2*max(w, h)*10+1} -delay 10 img/*.pgm {out}_solution.gif")
        print(f"{Color.green}Success !{Color.end}")
        os.system(f"rm img/*.pgm")

        print(f"{Color.blue}Filename : {Color.red}{out}_solution.gif{Color.end}")
    return

if __name__ == "__main__":
    argv = sys.argv
    out = "labyrinthe"

    if "--help" in argv or "-h" in argv:
        help()
        sys.exit(0)

    resolve = False
    if "--resolve" in argv:
        resolve = True

    if "--output" in argv:
        target = next_arg(argv, "--output")
        if target != None:
            out = target
    elif "-o" in argv: 
        target = next_arg(argv, "-o")
        if target != None:
            out = target
    
    w, h = 10, 10
    if "--geometry" in argv:
        geometry = next_arg(argv, "--geometry")
        if geometry != None:
            try:
                w, h = geometry.split('x')
                w, h = int(w), int(h)
            except ValueError:
                print(f"{Color.red}Error : Invalid geometry {Color.end}")
                help()
                sys.exit(1)
    
    
        
    main(out, w, h, resolve)