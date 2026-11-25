from random import randint
import corrige_pendu

#Question 0
#Compléter dans les chaînes ci-dessous, sans enlever les guillemets:
NOM = "Thieffry"
PRENOM = "Raphael"
EMAIL = "raphael.thieffry@universite-paris-saclay.fr"


#Question 1
def charge_mots(chemin):
    try:
        f = open(chemin, "r")
        lignes = f.readlines()
        bestMot = 0
        for i in range(len(lignes)):
            lignes[i] = lignes[i][:len(lignes[i])-1]
            if len(lignes[i])>bestMot:
                bestMot = len(lignes[i])
        f.close()
        return (lignes, bestMot)
    except FileNotFoundError:
       print("Le fichier", chemin, "n'existe pas !")

    except IsADirectoryError:
       print(chemin, "est un répertoire !")

    except PermissionError:
       print("Vous n'avez pas les droits en lecture sur le fichier", chemin)


#Question 2
def test_charge_mots():
    assert(charge_mots("mots.txt")[1]==25)
    assert(len(charge_mots("mots.txt")[0])==59705)
    assert(charge_mots("mots.txt")[0][0]=="abaissa")
    assert(charge_mots("mots.txt")[0][1]=="abaissai")

#Question 3
def mots_par_longueur(tab_mots, lmax):
    t = [[] for i in range(lmax+1)]
    for i in range(len(tab_mots)):
        if tab_mots[i] != "":
            t[len(tab_mots[i])].append(tab_mots[i])
    return t
#Question 4
def test_mots_par_longueur():
    assert(mots_par_longueur(['a', 'bonbon', 'code', 'dos', 'etre'], 6)== [ [], ['a'], [], ['dos'], ['code', 'etre'], [], ['bonbon'] ])
    assert(mots_par_longueur(['a', 'aa', 'aaaa', 'aaaaa', 'aaa', ''], 5) == [ [], ['a'], ['aa'], ['aaa'], ['aaaa'], ['aaaaa']])
#Question 5
def choix_mot(tab_mots_long, l):
    motsTailleL = tab_mots_long[l]
    return motsTailleL[randint(0,len(motsTailleL)-1)]
    
#Question 6
def test_choix_mot():
    #NE PAS MODIFIER LES 2 LIGNES SUIVANTES
    tab_mots, lmax = corrige_pendu.charge_mots("mots.txt")
    tab_mots_long = corrige_pendu.mots_par_longueur(tab_mots, lmax)
    #À COMPLÉTER CI-DESSOUS AVEC VOS TESTS, VOUS POUVEZ UTILISER
    #tab_mots_long POUR VOS TESTS
    assert(len(choix_mot(tab_mots_long, 8)) ==8 )
    assert(len(choix_mot(tab_mots_long, 6)) ==6 )
    assert(len(choix_mot(tab_mots_long, 25)) ==25 )


    return

#Question 7
def init_probleme(mot):
    t=[]
    for i in range(len(mot)):
        t.append((mot[i], False))
    return t
#Question 8
def test_init_probleme():
    assert(init_probleme('codex')==  [ ('c', False), ('o', False), ('d', False), ('e', False), ('x', False)])

#Question 9
def num_inconnues (probleme):
    counter = 0
    for i in range(len(probleme)):
        if probleme[i][1] == False:
            counter += 1
    return counter


# Question 10
def test_num_inconnues():
    assert(num_inconnues([ ('c', True), ('o', True), ('d', True), ('e', True), ('x', True)])==  0)
    assert(num_inconnues(init_probleme('saucisse')) == 8)
    assert(num_inconnues([ ('c', False), ('h', False), ('o', True), ('u', False), ('x', False)])==  4)

# Question 11
def joue(probleme, lettre):
    listecaselettre = []
    t = probleme + []
    for i in range(len(probleme)):
        if probleme[i][0] == lettre:
            listecaselettre.append(i)
    for i in range(len(listecaselettre)):
        t[listecaselettre[i]] = (lettre, True)
    return t
# Question 12
def test_joue():
    assert(joue([ ('c', True), ('o', True), ('d', True), ('e', False), ('x', True)],'e') == [('c', True), ('o', True), ('d', True), ('e', True), ('x', True)] )
    assert(joue(init_probleme('saucisse'),'s') == [('s', True), ('a', False), ('u', False), ('c', False), ('i', False),('s', True),('s', True), ('e', False)])
    assert(joue([ ('c', False), ('h', False), ('o', True), ('u', False), ('x', False)], 'z')==  [ ('c', False), ('h', False), ('o', True), ('u', False), ('x', False)])


# Question 13
def affiche_probleme(tab):
    chaine = ''
    for i in range(len(tab)):
        if tab[i][1] == True:
            chaine += tab[i][0]
        else:
            chaine += '.'
    print(chaine)


PENDU = (
    '  ___ ',
    ' |   |',
    ' o   |',
    '/|\  |',
    '/ \  |',
    '     |')

# Question 14
def affiche_pendu(n):
    k=0
    chaine = ''
    for i in range(len(PENDU)):
        for c in PENDU[i]:
            if c == ' ':
                chaine+=' '
            elif(k<n):
                chaine+=c
                k+=1
            else:
                chaine+=' '
        chaine+='\n'
    print(chaine)
# Question 15
def partie(mot):
    pb = init_probleme(mot)
    k=0
    while num_inconnues(pb) != 0 and k!=15:
        falseAvant = num_inconnues(pb)
        affiche_probleme(pb)
        inp = input("Une lettre entre a et z stp : ")
        while (len(inp) != 1) or (not(97<= ord(inp[0]) <=122)):
            inp = input("Une lettre entre a et z stp : ")
        inp = inp[0]
        pb = joue(pb,inp)
        falseApres = num_inconnues(pb)
        if falseAvant == falseApres:
            k +=1
        affiche_pendu(k)
    if k == 15:
        print("T'as perdu")
    else:
        print("T'as gagné (trop fort)")
#### NE PAS MODIFIER LE CODE CI-DESSOUS

def jeu():
    mots, lmax = charge_mots("mots.txt")
    lmots = mots_par_longueur(mots, lmax)
    while True:
        s = input("Saisir une longueur de mot ou q pour quitter: ")
        if s == 'q':
            print ("Au revoir.")
            return
        try:
            l = int(s)
            if l > lmax or l <= 0:
                print ("Longueur invalide")
                continue
            mot = choix_mot(lmots, l)
            partie (mot)
        except ValueError:
            print ("Saisie invalide")



jeu()
