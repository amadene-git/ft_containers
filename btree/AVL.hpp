//-----------------------------------------------------------------------
// PAR : Frederick Henri
//-----------------------------------------------------------------------
// Implantation d'un arbre AVL generique SANS doublon.
// Les erreurs sont gerees par des retours de fonction.
//-----------------------------------------------------------------------




#include <stdlib.h>




//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//							CLASSE NODE
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// Noeud de l'arbre.
// ATTENTION : Il ne faut pas mettre de destructeur dans le noeud. La
// destruction des sous-arbres sera geree par l'arbre, pas le noeud!
//-----------------------------------------------------------------------
template <class T>
class node
{
 public :
	T data;
	node * pere;
	node * filsg;
	node * filsd;

	node(const T & d);
	node(const T & d, node<T> * dad);
};


template <class T>
node<T>::node(const T & d)
{
	data = d;
	pere = filsg = filsd = NULL;
}


template <class T>
node<T>::node(const T & d, node<T> * dad)
{
	data = d;
	pere = dad;
	filsg = filsd = NULL;
}
//-----------------------------------------------------------------------
//							FIN DE LA CLASSE NODE
//-----------------------------------------------------------------------



//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//							CLASSE BINTREE
//-----------------------------------------------------------------------
// Cette classe permet de creer des arbres de n'importe quel type.
// Le type choisit doit permettre l'affectation (=).
//-----------------------------------------------------------------------
template <class T>
class bintree
{
 protected :
	node<T> * racine;	// Racine de l'arbre.
	int nb_noeuds;		// Nombre de noeuds de l'arbre.

	// On ne permet pas la copie (d'aucune sorte) !
	bintree(const bintree &);
	bintree& operator = (const bintree &);

	// Methodes privees recursives.
	void detruire_arbre(node<T> *);
	int profondeur_arbre(const node<T> *) const;
	int compter_feuilles_arbre(const node<T> *) const;

	void parcours_prefixe(const node<T> *, void (*f) (const T &)) const;
	void parcours_infixe(const node<T> *, void (*f) (const T &)) const;
	void parcours_suffixe(const node<T> *, void (*f) (const T &)) const;

	void parcours_prefixe(node<T> *, void (*f) (T &));
	void parcours_infixe(node<T> *, void (*f) (T &));
	void parcours_suffixe(node<T> *, void (*f) (T &));


 public :
	// CONSTRUCTEUR
	bintree() { racine = NULL; nb_noeuds = 0;}

	// DESTRUCTEUR
	virtual inline ~bintree() = 0;

	// METHODES DE MODIFICATION
	// Permet d'ajouter un element par rapport au courant.
	virtual int add(const T &) = 0;
	virtual int remove(const T &) = 0;

	// Vide l'arbre.
	virtual void empty();

	// Offre de parcours en modification.
	inline void prefix(void (*f) (T &)) { parcours_prefixe(racine, f);}
	inline void infix(void (*f) (T &))  { parcours_infixe(racine, f);}
	inline void suffix(void (*f) (T &)) { parcours_suffixe(racine, f);}


	// METHODES DE CONSULTATION
	// Offre de parcours en consultation.
	inline void prefix(void (*f) (const T &)) const { parcours_prefixe(racine, f);}
	inline void infix(void (*f) (const T &)) const  { parcours_infixe(racine, f);}
	inline void suffix(void (*f) (const T &)) const { parcours_suffixe(racine, f);}

	inline int size() const { return nb_noeuds;}	// Nombre de noeuds.
	inline int count_leaves() const					// Nombre de feuilles.
	{ return compter_feuilles_arbre(racine);}
	inline int depth() const                        // Profondeur de l'arbre.
	{ return profondeur_arbre(racine);}
};


//-----------------------------------------------------------------------
// 					METHODES PRIVEES DE BINTREE
//-----------------------------------------------------------------------
template <class T>
void bintree<T>::detruire_arbre(node<T> * arbre)
{
	if (arbre != NULL)
	{
		detruire_arbre(arbre->filsg);
		detruire_arbre(arbre->filsd);
		delete arbre;
	}
}

template <class T>
int bintree<T>::profondeur_arbre(const node<T> * arbre) const
{
	if (arbre == NULL)
		return 0;

	int prof_gauche = profondeur_arbre(arbre->filsg);
	int prof_droit = profondeur_arbre(arbre->filsd);
	return 1 + ((prof_gauche > prof_droit) ? prof_gauche : prof_droit);
}

template <class T>
int bintree<T>::compter_feuilles_arbre(const node<T> * arbre) const
{
	if (arbre == NULL)
		return 0;
	else if (arbre->filsg == NULL && arbre->filsd == NULL)
		return 1;
	else
		return compter_feuilles_arbre(arbre->filsg) +
			   compter_feuilles_arbre(arbre->filsd);
}


template <class T>
void bintree<T>::parcours_prefixe(const node<T> * arbre, void (*f) (const T &)) const
{
	if (arbre != NULL)
	{
		f(arbre->data);
		parcours_prefixe(arbre->filsg, f);
		parcours_prefixe(arbre->filsd, f);
	}
}

template <class T>
void bintree<T>::parcours_infixe(const node<T> * arbre, void (*f) (const T &)) const
{
	if (arbre != NULL)
	{
		parcours_infixe(arbre->filsg, f);
		f(arbre->data);
		parcours_infixe(arbre->filsd, f);
	}
}

template <class T>
void bintree<T>::parcours_suffixe(const node<T> * arbre, void (*f) (const T &)) const
{
	if (arbre != NULL)
	{
		parcours_suffixe(arbre->filsg, f);
		parcours_suffixe(arbre->filsd, f);
		f(arbre->data);
	}
}


template <class T>
void bintree<T>::parcours_prefixe(node<T> * arbre, void (*f) (T &))
{
	if (arbre != NULL)
	{
		f(arbre->data);
		parcours_prefixe(arbre->filsg, f);
		parcours_prefixe(arbre->filsd, f);
	}
}

template <class T>
void bintree<T>::parcours_infixe(node<T> * arbre, void (*f) (T &))
{
	if (arbre != NULL)
	{
		parcours_infixe(arbre->filsg, f);
		f(arbre->data);
		parcours_infixe(arbre->filsd, f);
	}
}

template <class T>
void bintree<T>::parcours_suffixe(node<T> * arbre, void (*f) (T &))
{
	if (arbre != NULL)
	{
		parcours_suffixe(arbre->filsg, f);
		parcours_suffixe(arbre->filsd, f);
		f(arbre->data);
	}
}



//-----------------------------------------------------------------------
// 					METHODES PUBLIQUES DE BINTREE
//-----------------------------------------------------------------------
template <class T>
bintree<T>::~bintree()
{
	if (nb_noeuds > 0)
	{
		detruire_arbre(racine->filsg);
		detruire_arbre(racine->filsd);
		delete racine;
	}
}


template <class T>
void bintree<T>::empty()
{
	if (nb_noeuds > 0)
	{
		detruire_arbre(racine->filsg);
		detruire_arbre(racine->filsd);
		delete racine;
		nb_noeuds = 0;
	}
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//						FIN DE LA CLASSE BINTREE
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------









//-----------------------------------------------------------------------
//							CLASSE SEARCH_TREE
//-----------------------------------------------------------------------
// Cette classe permet de creer des arbres binaires de fouille de
// n'importe quel type. Le type choisit doit permettre le (=) et le (<).
//-----------------------------------------------------------------------
template <class T>
class search_tree : public bintree<T>
{
 protected :
	// On ne permet pas la copie (d'aucune sorte) !
	search_tree(const search_tree &);
	search_tree& operator = (const search_tree &);

	node<T> * maximum(node<T> *) const;	// Adresse du maximum d'un arbre.
	node<T> * minimum(node<T> *) const;	// Adresse du minimum d'une arbre.

	node<T> * trouver_valeur(const T &) const;
	// Retourne l'adresse du noeud contenant la valeur.
	node<T> * trouver_pere(const T &) const;
	// Retourne l'adresse du pere d'un element que l'on ajoutera.

 public :
	// CONSTRUCTEUR ET DESTRUCTEUR
	search_tree() {}
	virtual inline ~search_tree() {}

	// METHODES DE MODIFICATION
	virtual int add(const T &);
	virtual int remove(const T &);

	// METHODES DE CONSULTATION
	inline int present(const T & element) const
	{ return (trouver_valeur(element) != NULL);}

	int maximum(T &) const;
	int minimum(T &) const;
};



//-----------------------------------------------------------------------
// 					METHODES PRIVEES DE SEARCH_TREE
//-----------------------------------------------------------------------
template <class T>
node<T> * search_tree<T>::maximum(node<T> * arbre) const
{
	if (arbre == NULL)
		return NULL;

	while (arbre->filsd != NULL)
		arbre = arbre->filsd;
	return arbre;
}


template <class T>
node<T> * search_tree<T>::minimum(node<T> * arbre) const
{
	if (arbre == NULL)
		return NULL;

	while (arbre->filsg != NULL)
		arbre = arbre->filsg;
	return arbre;
}


// Retourne l'adresse du noeud ou se situe une valeur (NULL si absente).
template <class T>
node<T> * search_tree<T>::trouver_valeur(const T & element) const
{
	// On cherche le pere.
	node<T> * noeud = this->racine;
	while (noeud != NULL && !(noeud->data == element))
		if (element < noeud->data)
			noeud = noeud->filsg;
		else
			noeud = noeud->filsd;
	return noeud;
}


// Retourne l'adresse du pere HYPOTHETIQUE d'un element A AJOUTER
// (non present dans l'arbre). Si l'arbre est vide, on retourne NULL.
template <class T>
node<T> * search_tree<T>::trouver_pere(const T & element) const
{
	if (this->nb_noeuds == 0)
		return NULL;

	// On cherche le pere.
	node<T> * pere = this->racine;
	int pere_trouve = 0;
	do
	{
		if (element < pere->data && pere->filsg != NULL)
			pere = pere->filsg;
		else if (pere->data < element && pere->filsd != NULL)
			pere = pere->filsd;
		else
			pere_trouve = 1;
	} while (!pere_trouve);
	return pere;
}



//-----------------------------------------------------------------------
// 					METHODES PUBLIQUES DE SEARCH_TREE
//-----------------------------------------------------------------------
template <class T>
int search_tree<T>::add(const T & element)
{
	// Si la valeur est deja la, on ne l'ajoute pas une seconde fois.
	if (present(element))
		return 0;

	// On trouve le pere, on cree le noeud et on verifie la memoire.
	node<T> * pere = trouver_pere(element);
	node<T> * nouveau = new node<T>(element, pere);
	if (nouveau == NULL)
		return 0;

	// On attache le pere et le fils.
	if (pere == NULL)
		this->racine = nouveau;
	else if (element < pere->data)
		pere->filsg = nouveau;
	else
		pere->filsd = nouveau;
	++(this->nb_noeuds);
	return 1;
}


template <class T>
int search_tree<T>::remove(const T & element)
{
	// On trouve l'element.
	node<T> * noeud = trouver_valeur(element);
	if (noeud == NULL)
		return 0;

	// On trouve le plus grand des plus petits.
	node<T> * remplacant = maximum(noeud->filsg);

	// S'il n'y a pas de remplacant, on escamote le noeud.
	if (remplacant == NULL)
	{
		if (noeud == this->racine)
			this->racine = noeud->filsd;
		else if (noeud->pere->filsg == noeud)
			noeud->pere->filsg = noeud->filsd;
		else
			noeud->pere->filsd = noeud->filsd;
		if (noeud->filsd != NULL)
			noeud->filsd->pere = noeud->pere;
	}
	else	// J'ai un maximum des minima.
	{
		noeud->data = remplacant->data;
		if (remplacant->pere->filsg == remplacant)
			remplacant->pere->filsg = remplacant->filsg;
		else
			remplacant->pere->filsd = remplacant->filsg;
		if (remplacant->filsg != NULL)
			remplacant->filsg->pere = remplacant->pere;
		noeud = remplacant;
	}
	delete noeud;
	--(this->nb_noeuds);
	return 1;
}


template <class T>
int search_tree<T>::maximum(T & element) const
{
	node<T> * noeud = maximum(this->racine);
	if (noeud == NULL)
		return 0;

	element = noeud->data;
	return 1;
}


template <class T>
int search_tree<T>::minimum(T & element) const
{
	node<T> * noeud = minimum(this->racine);
	if (noeud == NULL)
		return 0;

	element = noeud->data;
	return 1;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//						FIN DE LA CLASSE SEARCH_TREE
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------





//-----------------------------------------------------------------------
//							CLASSE AVL_TREE
//-----------------------------------------------------------------------
// Cette classe permet de creer des arbres binaires de fouille balances
// (AVL) de n'importe quel type.
// T doit supporter les operateurs : =, < et ==.
//-----------------------------------------------------------------------
template <class T>
class AVL_tree : public search_tree<T>
{
 private :
	// On ne permet pas la copie (d'aucune sorte) !
	AVL_tree(const AVL_tree &);
	AVL_tree& operator = (const AVL_tree &);

	void balance_tree(node<T> *);		// Appelle la rotation necessaire.
	void rotation_gauche(node<T> *);
	void rotation_droite(node<T> *);

 public :
	// CONSTRUCTEUR
	AVL_tree() {}

	// DESTRUCTEUR
	~AVL_tree() {}

	// METHODES DE MODIFICATION
	// Permettent d'ajouter et de retirer un element dans l'arbre.
	int add(const T &);
	int remove(const T &);
};



//-----------------------------------------------------------------------
// 					METHODES PRIVEES DE AVL_TREE
//-----------------------------------------------------------------------
template <class T>
void AVL_tree<T>::balance_tree(node<T> * arbre)
{
	if (arbre == NULL)				// Si l'arbre est vide, on ne fait rien.
		return;

	int balance_racine = this->profondeur_arbre(arbre->filsd) - this->profondeur_arbre(arbre->filsg);
	if (balance_racine == 2)		// Debalancement vers la droite.
	{
		int balance_filsd = this->profondeur_arbre(arbre->filsd->filsd) - this->profondeur_arbre(arbre->filsd->filsg);
		if (balance_filsd == -1)	// Cas de rotation droite-gauche.
			rotation_droite(arbre->filsd);
		rotation_gauche(arbre);
	}
	else if (balance_racine == -2)	// Debalancement vers la gauche.
	{
		int balance_filsg = this->profondeur_arbre(arbre->filsg->filsd) - this->profondeur_arbre(arbre->filsg->filsg);
		if (balance_filsg == 1)		// Cas de rotation gauche-droite.
			rotation_gauche(arbre->filsg);
		rotation_droite(arbre);
	}
	balance_tree(arbre->pere);
}


template <class T>
void AVL_tree<T>::rotation_gauche(node<T> * arbre)
{
	if (arbre == NULL)			// Si l'arbre est vide, on ne fait rien.
		return;

	node<T> * filsdroit = arbre->filsd;
	// On attache le parent de arbre au fils droit de arbre.
	if (arbre->pere != NULL)
	{	
		if (arbre->pere->filsd == arbre)
			arbre->pere->filsd = filsdroit;
		else
			arbre->pere->filsg = filsdroit;
	}
	filsdroit->pere = arbre->pere;

	// On lie arbre et le sous arbre gauche du fils droit.
	if (filsdroit->filsg != NULL)
		filsdroit->filsg->pere = arbre;
	arbre->filsd = filsdroit->filsg;

	// On place le fils droit comme sommet de arbre.
	arbre->pere = filsdroit;
	filsdroit->filsg = arbre;
	if (arbre == this->racine)
		this->racine = filsdroit;
}


template <class T>
void AVL_tree<T>::rotation_droite(node<T> * arbre)
{
	if (arbre == NULL)			// Si l'arbre est vide, on ne fait rien.
		return;

	node<T> * filsgauche = arbre->filsg;
	// On attache le parent de arbre au fils gauche de arbre.
	if (arbre->pere != NULL)
	{	
		if (arbre->pere->filsg == arbre)
			arbre->pere->filsg = filsgauche;
		else
			arbre->pere->filsd = filsgauche;
	}
	filsgauche->pere = arbre->pere;

	// On lie arbre et le sous arbre droit du fils gauche.
	if (filsgauche->filsd != NULL)
		filsgauche->filsd->pere = arbre;
	arbre->filsg = filsgauche->filsd;

	// On place le fils droit comme sommet de arbre.
	arbre->pere = filsgauche;
	filsgauche->filsd = arbre;
	if (arbre == this->racine)
		this->racine = filsgauche;
}



//-----------------------------------------------------------------------
// 					METHODES PUBLIQUES DE AVL_TREE
//-----------------------------------------------------------------------
template <class T>
int AVL_tree<T>::add(const T & element)
{
	// On ajoute l'element.
	if (search_tree<T>::add(element) == 0)
		return 0;

	// On garde l'arbre equilibre en balacant a partir du nouveau.
	balance_tree(this->trouver_valeur(element));
	return 1;
}


template <class T>
int AVL_tree<T>::remove(const T & element)
{
	// On conserve l'adresse du pere.
	node<T> * parent = this->trouver_valeur(element);
	parent = parent->pere;

	// On retire l'element.
	if (search_tree<T>::remove(element) == 0)
		return 0;

	// On rebalance l'arbre a partir du pere.
	balance_tree(parent);
	return 1;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//						FIN DE LA CLASSE AVL_TREE
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
