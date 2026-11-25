import java.util.EmptyStackException;

/*
* Classe Pile
* Structure de donnée de type LIFO (Last In First Out)
* Ne contient qu'un seul type de données, défini à l'instanciation
* de la classe. Contient les méthodes classique d'une Pile (push, pop, ...)
* Voir la classe pour plus de détails
*/

public class Pile<T> {
    /*
    * Construit une Pile vide
    * */
    public Pile(){};
    /*
     * Construit une Pile contenant tous les éléments
     * de arr, où l'élément 0 du tableau est en bas de la Pile
     * @param arr un tableau d'objet de type T
     * */
    public Pile(T[] arr){}
    /*
     * Ajoute un élément T en haut de la Pile
     * @param element un objet du type des objets de la Pile
     * */
    public void push(T element){}
    /*
     * Retire l'element en haut de la Pile
     * @throws EmptyStackException si la pile est vide
     * */
    public void pop() throws EmptyStackException {}
    /*
    * Renvoie la taille de la Pile
     */
    public int size(){
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
    * Convertie l'ensemble de la Pile sous la forme d'un
    * String
     */
    public String toString() {
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
    * Renvoie True si la Pile est vide, False sinon
     */
    public boolean isEmpty(){
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
    * Regarde le haut de la Pile sans le retirer
    * @throws EmptyStackException si la Pile est vide
     */
    public T peek() throws EmptyStackException{
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
     * Convertie la Pile en un tableau dans lequel l'element 0 est le bas de la Pile et
     * le dernier element du tableau est le haut de la Pile.
     */
    public T[] toArray(){
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
    * Renvoie la profondeur de l'element passé en paramètre
    * l'element en haut de la pile est considéré comme étant de profondeur 1
    * Renvoie -1 si l'element n'est pas dans la Pile
    * @param element un objet du type des éléments de la Pile, que l'on cherche dans la Pile
     */
    public int search(T element){
        throw new UnsupportedOperationException("Méthode non implémentée");
    }
    /*
    * Vide la Pile
     */
    public void clear(){}
    /*
    * Prend l'élément en haut de la Pile et le rempile de sorte
    * à ce que le premier et le deuxième élément soient les mêmes
    * @throws EmptyStackException si la Pile est vide
     */
    public void dup() throws EmptyStackException {}
    /*
     * Echange les deux éléments en haut de la Pile
     * @throws EmptyStackException si la Pile est vide ou ne contient qu'un seul
     * element
     */
    public void swap() throws EmptyStackException {}
}
