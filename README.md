# # ✅ Protocole de Test – Carte ELECE

Ce protocole permet de tester tous les éléments **pilotables ou mesurables** de la carte ELECE à l'aide de code exécuté sur l'ESP32-PICO-D4.

---

## 🔧 Éléments testables

| Composant               | GPIO             | Interface    | Testable | Méthode |
|-------------------------|------------------|--------------|----------|---------|
| LED Rouge               | CMD_LED_RED      | Digital Out  | ✅       | Allumage/Extinction |
| LED Verte               | CMD_LED_GREEN    | Digital Out  | ✅       | Allumage/Extinction |
| Buzzer                  | BUZZER-PWM (GPIO12) | PWM         | ✅       | Signal sonore (1 kHz) |
| CTN1 (Thermistance)     | GPIO34           | ADC          | ✅       | Lecture analogique variable |
| CTN2 (Thermistance)     | GPIO33           | ADC          | ✅       | Lecture analogique variable |
| TMP126 (Température)    | SPI (GPIO19/23/18/5) | SPI        | ✅       | Lecture température |
| INA237 (Mesure courant) | I2C (GPIO22/21)  | I2C          | ✅       | Lecture courant via shunt |
| UART USB/UART           | GPIO1/3          | UART         | ✅       | Test echo série |
| Bouton Reset / Boot     | GPIO0 / EN       | Digital In   | ✅       | Détection d’appui |
| Grove / Mikrobus        | Divers GPIO      | Connexions   | ❌       | Hors périmètre logiciel |

---

## 📋 Conditions de Validation

- **LEDs** : Allumage visuel OK (rouge + verte).
- **Buzzer** : Signal sonore audible.
- **CTN1/2** : Variation lecture ADC lors d’un changement de température.
- **TMP126** : Température lue cohérente (20–35 °C).
- **INA237** : Courant mesuré non nul si charge branchée.
- **UART** : Echo fonctionnel (TX → RX).
- **Boutons** : Lecture d’état logique qui change à l’appui.

---

## 🧪 Procédure de Test

1. Initialiser tous les GPIO nécessaires.
2. Tester LED rouge et verte (ON/OFF).
3. Activer le buzzer en PWM (fréquence typique : 1000 Hz).
4. Lire les valeurs ADC des CTN1 et CTN2.
5. Lire la température via TMP126 en SPI.
6. Lire le courant mesuré via INA237 en I2C.
7. Tester la communication UART (boucle RX/TX).
8. Lire l’état des boutons BOOT et RESET.
9. Enregistrer tous les résultats (PASS / FAIL).

---

## 🧷 Matériel Nécessaire

- PC avec moniteur série (PuTTY / Arduino IDE)
- Source de chaleur pour CTN (main ou briquet avec distance)
- Résistance de charge (pour test courant)
- Câble USB pour liaison série
- Oscilloscope (optionnel)

---

## ✅ Exemple de Résultat (à remplir)

| Test              | Résultat | Commentaire |
|-------------------|----------|-------------|
| LED Rouge         | ✅       | Allumage OK |
| LED Verte         | ✅       | Allumage OK |
| Buzzer            | ✅       | Son audible |
| CTN1              | ✅       | Valeur ADC varie |
| CTN2              | ✅       | Valeur ADC varie |
| TMP126 Temp       | ✅       | 26.5 °C stable |
| INA237 Courant    | ✅       | 122 mA mesurés |
| UART Echo         | ✅       | Données reçues identiques |
| Bouton GPIO0      | ✅       | Passage LOW à l’appui |

---

## 🛠️ Auteur du Test

- **Projet M1 ELECE - Validation de Carte**
- Réalisé par : [Nom Prénom]
- Date : [À compléter]
