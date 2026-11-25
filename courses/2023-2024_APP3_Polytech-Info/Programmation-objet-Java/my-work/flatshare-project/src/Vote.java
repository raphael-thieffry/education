public class Vote {
    final double note;
    final Colocataire votant;
    Vote(double note, Colocataire votant) throws IllegalArgumentException {
        /**
         * @param note: note (<10)
         * @param votant: votant
         */
        if(note < 0 || note > 10) throw new IllegalArgumentException("La note doit être comprise entre 0 et 10");
        this.note = note;
        this.votant = votant;
    }
    public boolean equals(Object o) {
        if(o instanceof Vote v) {
            return v.votant.equals(votant);
        }
        return false;
    }
}
