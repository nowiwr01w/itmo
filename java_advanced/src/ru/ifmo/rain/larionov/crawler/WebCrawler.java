package ru.ifmo.rain.larionov.crawler;

import info.kgeorgiy.java.advanced.crawler.*;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Phaser;

public class WebCrawler implements Crawler {

    private final Downloader downloader;
    private final ExecutorService extractors;
    private final ExecutorService downloaders;

    public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.downloader = downloader;
        this.downloaders = Executors.newFixedThreadPool(downloaders); // пул потоков, который использует фиксированное число потоков
        this.extractors = Executors.newFixedThreadPool(extractors);
    }

    public static void main(String[] args) {
        if (args.length != 5) {
            throw new IllegalArgumentException("Wrong count of arguments");
        }
        int depth, downloaders, extractors, perHost;
        try {
            depth = Integer.parseInt(args[1]); //
            downloaders = Integer.parseInt(args[2]);
            extractors = Integer.parseInt(args[3]);
            perHost = Integer.parseInt(args[4]);
        } catch (NumberFormatException | NullPointerException e) {
            throw new IllegalArgumentException("Incorrect arguments");
        }
        try {
            // CachingDownloader() - штука от Гоши, которая создает новый загрузчик, хранящий документы в каталоге.
            new WebCrawler(new CachingDownloader(), downloaders, extractors, perHost).download(args[0], depth);
        } catch (IOException e) {
            System.err.println("Error occurred while creating Downloader or downloading from the given url: " + e.getMessage());
        }
    }


    //  Должен рекурсивно обходить страницы, начиная с указанного URL на указанную глубину
    //  и возвращать список загруженных страниц и файлов
    @Override
    public Result download(String url, int depth) {
        // Phaser - это такая штука, на которой динамическое число потоков должно ждать, прежде чем продолжить выполнение.
        // В CountDownLatch этот номер не может быть настроен динамически и должен быть указан при создании экземпляра.
        Phaser phaser = new Phaser();
        // Создает новый фазер без изначально зарегистрированных сторон и с исходного номера фазы 0.
        // Любой поток, использующий этот фазер, должен сначала зарегистрироваться для него.
        Map<String, IOException> errors = new HashMap<>();
        Map<String, Boolean> visited = new ConcurrentHashMap<>(); // Потокобезопасность и Отсутствие блокировок всей таблицы на время доступа к ней
        Set<String> downloaded = ConcurrentHashMap.newKeySet();
        phaser.register(); // но его каждый раз нужно ручками регистрировать
        downloaders.submit(() -> {
            downloadPage(url, downloaded, errors, visited, depth, phaser);
            phaser.arrive(); // когда страница загружена, сообщаем, что сторона завершила фазу
        });
        phaser.awaitAdvance(0); // ждём, пока завершится 0 фаза, после чего возвращаем результат
        return new Result(new ArrayList<>(downloaded), errors);
    }

    private void downloadPage(String url, Set<String> downloaded, Map<String, IOException> errors,
                              Map<String, Boolean> visited, int depth, Phaser phaser) {
        if (visited.putIfAbsent(url, true) == null) {
            try {
                Document document = downloader.download(url);
                downloaded.add(url);
                if (depth > 1) {
                    phaser.register(); // регистрируем сторону, которая выполняет фазы
                    extractors.submit(() -> {
                        extractLinks(document, downloaded, errors, visited, depth, phaser); // извлекаем ссылки
                        phaser.arrive(); // сообщаем, что сторона завершила фазу
                    });
                }
            } catch (IOException e) {
                errors.put(url, e); // если произошла ошибка, кладём её в мапу, чтобы потом вернуть Result
            }
        }
    }

    private void extractLinks(Document document, Set<String> downloaded, Map<String, IOException> errors,
                              Map<String, Boolean> visited, int depth, Phaser phaser) {
        try {
            for (String link : document.extractLinks()) {
                phaser.register(); // регистрируем сторону, которая выполняет фазы
                downloaders.submit(() -> {
                    downloadPage(link, downloaded, errors, visited, depth - 1, phaser);
                    phaser.arrive(); // сообщаем, что сторона завершила фазу
                });
            }
        } catch (IOException ignored) { }
    }

    @Override
    public void close() {
        downloaders.shutdownNow();
        extractors.shutdownNow();
    }
}