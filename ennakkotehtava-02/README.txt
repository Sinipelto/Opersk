ennakkokysymykset:

a) Luokan ja rajapinnan ero:

Luokka on tietyllä tavalla olion "pohjapiirros", luomisohje kääntäjälle,
millaisia ominaisuuksia ja toimintoja luokasta syntyvällä oliolla on.
Luokan rakentajassa on määritelty olion ominaisuudet, eli attribuutit
(esim. olio: ihminen - ominaisuuksia: pituus, paino, ikä, nimi jne).
Oliolle voidan myös määritellä toimintoja eli metodeja
(esim. olio: ihminen - toimintoja: syödä, nukkua, kävellä, puhua).

Luokasta voidaan luoda useita olioita, joilla voi mahdollisesti olla
keskenään erisuuret ominaisuudet (esim eri ikä tai pituus), mutta
ne ovat tyypiltään samanlaisia olioita, sillä ne on luotu samasta luokasta
ja niillä on tällöin samat attribuutit ja metodit.


b) Julkinen rajapinta

Julkinen rajapinta eli "työkalu" on tyypiltään sellainen rajapinta, j
onka toiminta on julkista, eli kuka tahansa saa tietää,
miten se toimii ja se on kaikkien käytettävissä.

c) Yksityinen rajapinta

Yksityinen rajapinta puolestaan sisältää algoritmeja, joiden toiminta-
periaatteet ovat tiedossa vain kehittäjillään (ja mahdollisesti muilla
asianomaisilla) mutta eivät julkisessa tiedossa.

Rajapinta voi olla myös osittain avoin niin, että sitä voidaan kehittää
tai sillä voidaan luoda uusia ohjelmia muidenkin toimesta,
mutta varsinaista koodin toimintatapaa tai algoritmeja ei tiedetä.
Näin voidaan esimerkiksi estää lähdekoodin suora kopioiminen tai tietoturva-
aukkojen paljastuminen. (esim. Windows, yksityinen lähdekoodi, mutta avoin
rajapinta windows-ohjelmistojen kehittäjille).
