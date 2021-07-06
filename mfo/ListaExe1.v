Require Import Coq.Arith.PeanoNat.

(* BCC - MFO 2021/1 *)
(* Paulo Roberto Albuquerque *)

Fixpoint div2 (n:nat) : nat :=
  match n with
  | O => O
  | S O => O 
  | S (S n') => S (div2 n')  
end.  

Fixpoint sum (n : nat) : nat :=
  match n with
  | O => O
  | S n' => n + sum n'
  end.

Theorem mult_comm : forall m n : nat,
  m * n = n * m.
Proof.
  Admitted.

Theorem plus_assoc: forall n m p : nat,
  n + (m + p) = (n + m) + p.
Proof.
  intros n m p. induction n as [| n' IHn'].
  - (* n = 0 *)
    reflexivity.
  - (* n = S n' *)
    simpl. rewrite -> IHn'. reflexivity.
Qed.

Theorem plus_n_1 : forall (n : nat),
  n + 1 = S (n).
Proof.
  simpl. intro. induction n as [| n IH].
  - simpl. reflexivity.
  - simpl. rewrite IH. reflexivity.
Qed.


Theorem plus_n_Sm : forall (n m:nat),
  n + S m = S (n + m).
Proof. 
  intros m n. rewrite Nat.add_comm. simpl. rewrite Nat.add_comm.
  reflexivity.
Qed.

Theorem mult_2_n_plus : forall (n : nat),
  n + n = 2 * n.
Proof.
  intro. destruct n as [|n'].
  - reflexivity.
  - simpl. rewrite <- plus_n_O. reflexivity.
Qed.

Theorem mul2_div2 : forall n : nat,
  n = div2 (2 * n).
Proof.
  intro. induction n as [|n' IH].
  - reflexivity.
  - rewrite Nat.mul_succ_l. rewrite Nat.mul_1_l. rewrite mult_2_n_plus.
  rewrite Nat.mul_comm. simpl. rewrite Nat.mul_comm. rewrite <- IH. reflexivity.
Qed.

Theorem div2_mult2_plus: forall (n m : nat),
  n + div2 m = div2 (2 * n + m).
Proof.
  simpl. intros n m. induction n as [|n IH].
  - simpl. reflexivity.
  - simpl. rewrite plus_n_Sm. rewrite IH. reflexivity.
Qed.

Theorem mult_Sn_m : forall (n m : nat),
  S n * m = m + n * m.
Proof.
  simpl. intros n m. reflexivity.
Qed.

Theorem sum_Sn : forall n : nat,
  sum (S n) = S n + sum n.
Proof.
  simpl. intro. reflexivity.
Qed.


Theorem sum_n : forall n : nat,
  sum n = div2 (n * (n + 1)).
Proof.
simpl. intro. induction n as [|n IH].
  - simpl. reflexivity.
  -  rewrite plus_n_1. rewrite mult_comm. rewrite mult_Sn_m. rewrite mult_Sn_m.
  rewrite plus_assoc. rewrite mult_2_n_plus. rewrite sum_Sn. rewrite <- plus_n_1.
  rewrite <- div2_mult2_plus. rewrite IH. reflexivity.
Qed.