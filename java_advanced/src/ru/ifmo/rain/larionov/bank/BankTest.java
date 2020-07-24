package ru.ifmo.rain.larionov.bank;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

import static org.junit.Assert.*;

@RunWith(JUnit4.class)
public class BankTest {

    private static final int PORT = 8890;
    private static Bank bank;

    private final int id = 1;
    private final String firstName = "first";
    private final String lastName = "second";
    private final String accountName = "accountName";

    // Registry это удаленный интерфейс к простому реестру удаленных объектов, который предоставляет методы для
    // хранения и извлечения ссылок на удаленные объекты, связанные с произвольными строковыми именами.
    // Методы bind, unbind и rebind используются для изменения привязок имен в реестре, а методы поиска и списка
    // используются для запроса текущих привязок имен.
    private static Registry registry;

    @BeforeClass
    public static void beforeAll() throws RemoteException {
        registry = LocateRegistry.createRegistry(PORT);
    }

    @Before
    public void beforeEach() throws RemoteException {
        bank = new RemoteBank(PORT);
        // Экспортирует удаленный объект, чтобы сделать его доступным для приема входящих вызовов, используя определенный предоставленный порт.
        Bank stub = (Bank) UnicastRemoteObject.exportObject(bank, PORT);
        // Заменяет привязку для указанного имени в этом реестре с предоставленным удаленным объектом.
        registry.rebind("bank", stub);
    }


    @Test
    public void changeMoney() throws RemoteException {
        // создаём 10 пользователей
        for (var i = 0; i < 10; ++i) {
            assertTrue(bank.createPerson(id + i, firstName + i, lastName + i));
            bank.getRemotePerson(id + i);
        }
        // пусть у каждого будет 10 счетов
        for (var i = 0; i < 10; ++i) {
            Person person = bank.getRemotePerson(id + i);
            for (var j = 0; j < 10; ++j) {
                bank.createAccount(person, "Account" + j);
            }
        }
        // изначально на каждом счету было 0, прибавик к каждому счёту по 200 и сделаем ассерт
        for (var i = 0; i < 10; ++i) {
            Person person = bank.getRemotePerson(id + i);
            for (var j = 0; j < 10; ++j) {
                Account account = bank.getAccount(person, "Account" + j);
                System.out.println("Account id: " + account.getId());
                System.out.println("Money: " + account.getMoney());
                System.out.println("Changing amount...");
                account.setMoney(account.getMoney() + 200);
                System.out.println("Money: " + account.getMoney());
                assertEquals(200, account.getMoney());
            }
        }
        // ну и у каждого вычтем 200 и проверим ассерт на нулевую сумму
        for (var i = 0; i < 10; ++i) {
            Person person = bank.getRemotePerson(id + i);
            for (var j = 0; j < 10; ++j) {
                Account account = bank.getAccount(person, "Account" + j);
                System.out.println("Account id: " + account.getId());
                System.out.println("Money: " + account.getMoney());
                System.out.println("Changing amount...");
                account.setMoney(account.getMoney() - 200);
                System.out.println("Money: " + account.getMoney());
                assertEquals(0, account.getMoney());
            }
        }
    }

    @Test
    public void createOneRemotePerson() throws RemoteException {
        // Проверяем, что успешно создали пользователя
        assertTrue(bank.createPerson(id, firstName, lastName));
        Person remotePerson = bank.getRemotePerson(id);
        // Проверяем, что все его данные верные
        assertEquals(remotePerson.getPassportId(), id);
        assertEquals(remotePerson.getFirstName(), firstName);
        assertEquals(remotePerson.getLastName(), lastName);
    }

    @Test
    public void createOneRemoteLocalPerson() throws RemoteException {
        assertTrue(bank.createPerson(id, firstName, lastName));
        Person localPerson = bank.getLocalPerson(id);
        assertEquals(localPerson.getPassportId(), id);
        assertEquals(localPerson.getFirstName(), firstName);
        assertEquals(localPerson.getLastName(), lastName);
    }

    @Test
    public void amountAccountsByPerson() throws RemoteException {
        bank.createPerson(id, firstName, lastName);
        Person remotePerson = bank.getRemotePerson(id);
        // Пытаемся создать 100 аккаубнтов, но должно создастся только 10. Проверим это
        for (var i = 0; i < 10; ++i) {
            for (var j = 0; j < 10; ++j) {
                bank.createAccount(remotePerson, Integer.toString(j));
            }
        }
        Set<String> accounts = bank.getAccountsByPerson(remotePerson);
        assertEquals(accounts.size(), 10);
    }

    @Test
    public void createOnePersonTwice() throws RemoteException {
        // Смотрим предыдущий тест, логика та же
        assertTrue(bank.createPerson(id, firstName, lastName));
        assertFalse(bank.createPerson(id, firstName, lastName));
    }

    @Test
    public void createManyPerson() throws RemoteException {
        int count = 1000;
        for (int i = 0; i < count; i++) {
            // Создаём уникального пользователя
            assertTrue(bank.createPerson(i, firstName + i, lastName + i));

            // Проверяем его данные
            Person remotePerson = bank.getRemotePerson(i);
            assertEquals(remotePerson.getPassportId(), i);
            assertEquals(remotePerson.getFirstName(), firstName + i);
            assertEquals(remotePerson.getLastName(), lastName + i);

            // Проверяем его данные
            Person localPerson = bank.getLocalPerson(i);
            assertEquals(localPerson.getPassportId(), i);
            assertEquals(localPerson.getFirstName(), firstName + i);
            assertEquals(localPerson.getLastName(), lastName + i);
        }
    }

    @Test
    public void getPersonWithoutCreating() throws RemoteException {
        assertNull(bank.getLocalPerson(1234));
    }

    @Test
    public void createOneAccountRemotePerson() throws RemoteException {
        bank.createPerson(id, firstName, lastName);
        // Создадим одного удалённого пользователя, а затем аккаунт у него
        Person remotePerson = bank.getRemotePerson(id);
        assertTrue(bank.createAccount(remotePerson, accountName));
        Account account = bank.getAccount(remotePerson, accountName);
        // И проверим, что все данные для аккаунта верные
        assertEquals(account.getId(), accountName);
        assertEquals(account.getMoney(), 0);
    }

    @Test
    public void createOneAccountLocalPerson() throws RemoteException {
        bank.createPerson(id, firstName, lastName);
        // Аналогично предыдущему, только создаём локального пользователя
        Person localPerson = bank.getLocalPerson(id);
        assertTrue(bank.createAccount(localPerson, accountName));
        Account account = bank.getAccount(localPerson, accountName);
        assertEquals(account.getId(), accountName);
        assertEquals(account.getMoney(), 0);
    }

    @Test
    public void createOneAccountRemotePersonTwice() throws RemoteException {
        bank.createPerson(id, firstName, lastName);

        Person remotePerson = bank.getRemotePerson(id);
        assertTrue(bank.createAccount(remotePerson, accountName));
        assertFalse(bank.createAccount(remotePerson, accountName));
    }

    @Test
    public void getAccountWithoutCreating() throws RemoteException {
        bank.createPerson(id, firstName, lastName);

        Person person = bank.getRemotePerson(id);
        Account account = bank.getAccount(person, "1234");
        assertEquals(account.getMoney(), 0);
        account.setMoney(account.getMoney() + 322);
        assertEquals(account.getMoney(), 322);
        account.setMoney(account.getMoney() - 322);
        assertNotEquals(322, account.getMoney());
        assertEquals(account.getMoney(), 0);
    }

    @Test
    public void createOneAccountLocalPersonTwice() throws RemoteException {
        bank.createPerson(id, firstName, lastName);

        Person localPerson = bank.getLocalPerson(id);
        assertTrue(bank.createAccount(localPerson, accountName));
        assertFalse(bank.createAccount(localPerson, accountName));
    }

    @Test
    public void createManyAccount() throws RemoteException {
        int peopleCount = 100;
        int randomMax = 100;
        Random random = new Random();
        for (int i = 0; i < peopleCount; i++) {
            bank.createPerson(i, firstName, lastName);
            Person remotePerson = bank.getRemotePerson(i);
            int accountCount = Math.abs(random.nextInt(randomMax));
            for (int j = 0; j < accountCount; j++) {
                bank.createAccount(remotePerson, accountName + j);
            }
            assertEquals(bank.getAccountsByPerson(remotePerson).size(), accountCount);
        }
    }

    @Test
    public void setAccountAmountRemotePerson() throws RemoteException {
        int amount = 542;
        bank.createPerson(id, firstName, lastName);

        Person localPerson = bank.getLocalPerson(id);
        Person remotePerson = bank.getRemotePerson(id);

        bank.createAccount(remotePerson, accountName);
        Account account = bank.getAccount(remotePerson, accountName);

        // Так акак счёь только у удалённого пользователя
        assertNull(bank.getAccount(localPerson, accountName));
        localPerson = bank.getLocalPerson(id);

        account.setMoney(amount);

        account = bank.getAccount(remotePerson, accountName);
        assertEquals(account.getId(), accountName);
        assertEquals(account.getMoney(), amount);

        account = bank.getAccount(localPerson, accountName);
        assertEquals(account.getMoney(), 0);

        localPerson = bank.getLocalPerson(id);
        account = bank.getAccount(localPerson, accountName);
        assertEquals(account.getMoney(), amount);
    }

    @Test
    public void setAccountAmountLocalPerson() throws RemoteException {
        final int amount = 542;
        bank.createPerson(id, firstName, lastName);

        Person localPerson = bank.getLocalPerson(id);
        bank.createAccount(localPerson, accountName);
        Account account = bank.getAccount(localPerson, accountName);
        account.setMoney(amount);

        assertEquals(account.getMoney(), amount);

        Person remotePerson = bank.getRemotePerson(id);
        account = bank.getAccount(remotePerson, accountName);
        assertEquals(account.getMoney(), 0);
    }


    @Test
    public void checkAndCreateOnePerson() throws RemoteException {
        assertFalse(bank.getPerson(id, firstName + id, lastName + id));
        bank.createPerson(id, firstName + id, lastName + id);
        assertTrue(bank.getPerson(id, firstName + id, lastName + id));
    }


    @Test
    public void checkAndCreateManyPerson() throws RemoteException {
        int count = 1000;
        for (int i = 0; i < count; ++i) {
            assertFalse(bank.getPerson(i, firstName + i, lastName + i));
            bank.createPerson(i, firstName + i, lastName + i);
            assertTrue(bank.getPerson(i, firstName + i, lastName + i));
        }
    }

    @Test
    public void checkSomeUserCreateManyAccount() throws RemoteException {
        int peopleCount = 100;
        int accountCount = 100;
        bank.createPerson(id, firstName, lastName);
        List<Person> people = new ArrayList<>();
        for (int i = 0; i < peopleCount; ++i) {
            people.add(bank.getRemotePerson(id));
        }
        for (int i = 0; i < accountCount; i++) {
            for (int j = 0; j < peopleCount; j++) {
                assertTrue(bank.createAccount(people.get(j), "person" + j + "account" + i));
            }
        }
        for (int i = 0; i < peopleCount; i++) {
            assertEquals(bank.getAccountsByPerson(people.get(i)).size(), accountCount * peopleCount);
        }
    }

    @Test
    public void checkSomeUserSetAmount() throws RemoteException {
        int peopleCount = 100;
        int accountCount = 100;
        List<Person> people = new ArrayList<>();
        for (int i = 0; i < peopleCount; ++i) {
            bank.createPerson(i, firstName, lastName);
            people.add(bank.getRemotePerson(i));
        }
        Map<String, Integer> answer = new HashMap<>();
        Random random = new Random();
        for (int i = 0; i < accountCount; i++) {
            for (int j = 0; j < peopleCount; j++) {
                final String accountId = "person" + j + "account" + i;
                bank.createAccount(people.get(j), accountId);
                Account account = bank.getAccount(people.get(j), accountId);
                int value = Math.abs(random.nextInt());
                account.setMoney(value);
                answer.put(accountId, value);
            }
        }
        for (int i = 0; i < accountCount; i++) {
            for (int j = 0; j < peopleCount; j++) {
                final String accountId = "person" + j + "account" + i;
                assertEquals(bank.getAccount(people.get(j), accountId).getMoney(), answer.get(accountId).intValue());
            }
        }
    }
}