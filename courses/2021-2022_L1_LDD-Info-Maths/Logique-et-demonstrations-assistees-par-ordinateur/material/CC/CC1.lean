import Mdd154.Lib
setup_env

-- # Nom :
-- # Prénom :
-- # Renommer le fichier en CC1_Nom_Prenom.lean avant de le déposer sur eCampus.

-- # CC1 - Compléter le code Lean ci-dessous.

/-
N’oubliez pas de taper

getexomdd154 seance8

avant de commencer (et relancer VScode si vous l’aviez lancé avant le getexomdd154).

`m est borne inf de u` signifie
  (∀ n, m ≤ u n) ∧ ∀ ε > 0, ∃ n₀, u n₀ ≤ m + ε
-/
Exercice "Toute suite décroissante ayant une borne inférieure tend vers cette borne"
  Données : (u : ℕ → ℝ) (m : ℝ)
  Hypothèses : (h : m est borne inf de u) (h' : u est décroissante)
  Conclusion : u tend vers m
Démonstration :
  sorry
QED
