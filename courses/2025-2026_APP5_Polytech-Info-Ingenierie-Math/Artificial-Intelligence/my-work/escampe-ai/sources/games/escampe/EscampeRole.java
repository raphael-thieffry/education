package games.escampe;

import iialib.games.model.IRole;

/** Rôles Escampe pour iialib. */
public enum EscampeRole implements IRole {
    BLANC, NOIR;

    /** Chaîne attendue par {@link Partie1} : "blanc" ou "noir". */
    public String partie1String() {
        return this == BLANC ? "blanc" : "noir";
    }

    public EscampeRole opponent() {
        return this == BLANC ? NOIR : BLANC;
    }

    public static EscampeRole fromPartie1String(String s) {
        if ("blanc".equalsIgnoreCase(s)) return BLANC;
        if ("noir".equalsIgnoreCase(s)) return NOIR;
        throw new IllegalArgumentException("Rôle inconnu : " + s);
    }
}
