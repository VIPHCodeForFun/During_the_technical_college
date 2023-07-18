-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 15, 2021 at 12:14 PM
-- Server version: 10.1.38-MariaDB
-- PHP Version: 7.3.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `hian`
--

-- --------------------------------------------------------

--
-- Table structure for table `article`
--

CREATE TABLE `article` (
  `id` int(11) NOT NULL,
  `category_id` int(11) NOT NULL DEFAULT '0',
  `section_id` int(11) NOT NULL DEFAULT '0',
  `creationtime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `header` varchar(255) NOT NULL DEFAULT '',
  `text` text NOT NULL,
  `image` varchar(255) NOT NULL DEFAULT '',
  `url` varchar(255) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `article`
--

INSERT INTO `article` (`id`, `category_id`, `section_id`, `creationtime`, `header`, `text`, `image`, `url`) VALUES
(1, 5, 2, '2020-12-08 11:16:26', '8K ist eine TV-Revolution ohne Revolutionäre', 'Auf der Elektronikmesse IFA soll die Auflösung 8K das nächste Fernsehzeitalter einläuten - ohne 8K-Inhalte.', 'index_1.jpg', '#'),
(2, 5, 2, '2020-12-08 11:16:26', 'Geleakte Fotos zeigen iPhone XS und Apple Watch Series 4', 'Offizielle Fotos der neuen Apple-Geräte sind knapp zwei Wochen vor der Präsentation an die Öffentlichkeit geraten.', 'index_2.jpg', '#'),
(3, 6, 2, '2020-12-08 11:16:26', 'ISS-Astronaut schließt Loch in Raumstation mit Daumen', 'ISS-Kommandant Alexander Gerst hat eine ungewöhnliche Lösung gefunden, um ein kleines Loch zu schließen.', 'index_3.jpg', '#'),
(4, 3, 2, '2020-12-08 11:16:26', 'Nach Online-Umfrage: EU-Kommission will Zeitumstellung abschaffen', 'EU-Kommissionspräsident Jean-Claude Juncker will sich nach dem Ergebnis der Online-Umfrage richten und spricht sich für eine \"dauerhafte Sommerzeit\" aus.', 'index_5.jpg', '#'),
(5, 3, 2, '2020-12-08 11:16:26', 'Google steckt Mensch in Riesen-Automat, um Sprachsteuerung zu bewerben', 'Auf der IFA ist ein überdimensionaler Automat aufgestellt, bei dem Besucher Preise kriegen, wenn sie den Google Assistent Fragen stellen.', 'index_4.jpg', '#'),
(6, 5, 2, '2020-12-08 11:16:26', '8K ist eine TV-Revolution ohne Revolutionäre', 'Auf der Elektronikmesse IFA soll die Auflösung 8K das nächste Fernsehzeitalter einläuten - ohne 8K-Inhalte.', 'index_8.jpg', '#'),
(7, 5, 2, '2020-12-08 11:16:26', 'Geleakte Fotos zeigen iPhone XS und Apple Watch Series 4', 'Offizielle Fotos der neuen Apple-Geräte sind knapp zwei Wochen vor der Präsentation an die Öffentlichkeit geraten.', 'index_7.jpg', '#'),
(10, 3, 2, '2020-12-08 11:16:26', 'Google steckt Mensch in Riesen-Automat, um Sprachsteuerung zu bewerben', 'Auf der IFA ist ein überdimensionaler Automat aufgestellt, bei dem Besucher Preise kriegen, wenn sie den Google Assistent Fragen stellen.', 'index_3.jpg', '#'),
(11, 5, 3, '2020-12-08 11:16:26', '8K ist eine TV-Revolution ohne Revolutionäre', 'Auf der Elektronikmesse IFA soll die Auflösung 8K das nächste Fernsehzeitalter einläuten - ohne 8K-Inhalte.', 'index_1.jpg', '#'),
(12, 5, 3, '2020-12-08 11:16:26', 'Geleakte Fotos zeigen iPhone XS und Apple Watch Series 4', 'Offizielle Fotos der neuen Apple-Geräte sind knapp zwei Wochen vor der Präsentation an die Öffentlichkeit geraten.', 'index_9.jpg', '#'),
(13, 6, 3, '2020-12-08 11:16:26', 'ISS-Astronaut schließt Loch in Raumstation mit Daumen', 'ISS-Kommandant Alexander Gerst hat eine ungewöhnliche Lösung gefunden, um ein kleines Loch zu schließen.', 'index_8.jpg', '#'),
(15, 3, 3, '2020-12-08 11:16:26', 'Google steckt Mensch in Riesen-Automat, um Sprachsteuerung zu bewerben', 'Auf der IFA ist ein überdimensionaler Automat aufgestellt, bei dem Besucher Preise kriegen, wenn sie den Google Assistent Fragen stellen.', 'index_4.jpg', '#'),
(16, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Samsung bestätigt: Faltbares Smartphone kommt noch dieses Jahr', 'index_6.jpg', '#'),
(17, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Tesla bringt langsames Akkupack für Smartphones', 'index_5.jpg', '#'),
(18, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Die deutschen Autohersteller starten den Angriff auf Tesla', 'index_2.jpg', '#'),
(19, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Neue Bilder des nächsten Tesla Roadster veröffentlicht', 'index_1.jpg', '#'),
(20, 4, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Epic zeigt neuen Modus für Fortnite', 'index_0.jpg', '#'),
(21, 3, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Start abgebrochen: Teenager schickt Tatort-Foto an alle iPhones im Flugzeug', 'index_5.jpg', '#'),
(22, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Xiaomi will High-End-Smartphone für 250 Euro anbieten', 'index_7.jpg', '#'),
(23, 3, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Netflix will nichts mit “Binge-Watching” zu tun haben', 'index_4.jpg', '#'),
(24, 3, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Video: Dreamliner versucht während Taifun zu landen', 'index_2.jpg', '#'),
(25, 5, 4, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Das erste E-Auto von Mercedes setzt auf ein futuristisches Innendesign', 'index_6.jpg', '#'),
(26, 1, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Teslas Chefbuchhalter AND <b>Finanzminister</b> tritt nach nur einem Monat wieder ab', 'index_1.jpg', '#'),
(27, 2, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Opposition drängt Finanzminister auf Digitalsteuer', 'index_0.jpg', '#'),
(28, 3, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'So spotten die Internet-Nutzer über den kiffenden Elon Musk', 'index_9.jpg', '#'),
(29, 1, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Hofer erforscht mit FH Oberösterreich die Zukunft des Handels', 'index_5.jpg', '#'),
(30, 1, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Bäckerei Felber finanziert Solarstromanlage über Crowdfunding', 'index_7.jpg', '#'),
(31, 4, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Erstes Video von Battle-Royale-Modus für Call of Duty', 'index_8.jpg', '#'),
(32, 1, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Venezuela: Kryptowährung Petro wird zum Superflop', 'index_2.jpg', '#'),
(33, 5, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Leak soll Nokia 9 mit fünf Kameras zeigen', 'index_6.jpg', '#'),
(34, 0, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'Neuer Tor Browser 8 macht anonymes Surfen bequemer', 'index_5.jpg', '#'),
(35, 3, 1, '2020-12-08 11:16:26', 'Dies ist ein Header', 'US-Start-up Lime startet mit Tretroller-Sharing in Wien', 'index_0.jpg', '#');

-- --------------------------------------------------------

--
-- Table structure for table `category`
--

CREATE TABLE `category` (
  `id` int(11) NOT NULL,
  `label` varchar(255) NOT NULL DEFAULT '',
  `title` varchar(255) NOT NULL DEFAULT '',
  `color` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `category`
--

INSERT INTO `category` (`id`, `label`, `title`, `color`) VALUES
(1, 'b2b', 'Business to Business', '#95afc0'),
(2, 'netzpolitik', 'Netzpolitik', '#c7ecee'),
(3, 'digital-life', 'Digital Life', '#535c68'),
(4, 'games', 'Games', '#22a6b3'),
(5, 'produkte', 'Produkte', '#f9ca24'),
(6, 'science', 'Science', '#badc58');

-- --------------------------------------------------------

--
-- Table structure for table `section`
--

CREATE TABLE `section` (
  `id` int(11) NOT NULL,
  `route` varchar(255) NOT NULL DEFAULT '',
  `label` varchar(100) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `section`
--

INSERT INTO `section` (`id`, `route`, `label`) VALUES
(1, 'newest', 'Newest'),
(2, 'current', 'Current'),
(3, 'main', 'Main'),
(4, 'mostread', 'Most Read');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `article`
--
ALTER TABLE `article`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `category`
--
ALTER TABLE `category`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `section`
--
ALTER TABLE `section`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `article`
--
ALTER TABLE `article`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=36;

--
-- AUTO_INCREMENT for table `category`
--
ALTER TABLE `category`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT for table `section`
--
ALTER TABLE `section`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
