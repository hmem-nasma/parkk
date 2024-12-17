int Ajout_Utilisateur(char login[110], char password[110], char nom[110], char role[110]);
int Verifier_Utilisateur(char login[110], char password[110]);
int Ajout_Parking(int numero, char nom[110], int capacite, float prix, int jour, int mois, int annee, char adresse[110], char securite[500], char secteur[110], char agent[110]);
int Rechercher_Parking(int numero, char *nom, int *capacite, float *prix, int *jour, int *mois, int *annee, char *adresse, char *securite, char *secteur);
int Modifier_Parking(int numero,char *nouveau_nom, int nouvelle_capacite, float nouveau_prix, int nouveau_jour, int nouveau_mois, int nouvelle_annee,char *nouvelle_adresse,  char *nouvelle_securite, 
 char *nouveau_secteur);
int Rechercher_Noms_Parking(char noms[][110], int taille_max);
int Supprimer_Parking(const char *nom_parking);
int Rechercher_Parkings_Sans_Agent(char noms[][110], int taille_max);
int Rechercher_ID_Agents(char ids[][110], int taille_max);
int affectAgent(char *nom_parking, char *id_agent);
