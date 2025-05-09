

-- 创建Customers表
CREATE TABLE Customers (
    CustomerID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    Name VARCHAR(50) NOT NULL,
    Email VARCHAR(100) NOT NULL UNIQUE CHECK (Email REGEXP '^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$'),
    Phone VARCHAR(20) CHECK (Phone REGEXP '^((13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])[0-9]{8})|((0[0-9]{2,3})-?([0-9]{7,8}))$'),
    RegistrationDate DATE NOT NULL
);

-- 添加默认日期的触发器
DELIMITER $$
CREATE TRIGGER set_registration_date
BEFORE INSERT ON Customers
FOR EACH ROW
BEGIN
    IF NEW.RegistrationDate IS NULL THEN
        SET NEW.RegistrationDate = CURRENT_DATE;
    END IF;
END$$
DELIMITER ;

-- 创建Categories表
CREATE TABLE Categories (
    CategoryID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    CategoryName VARCHAR(50) NOT NULL UNIQUE
);

-- 创建Products表
CREATE TABLE Products (
    ProductID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    ProductName VARCHAR(100) NOT NULL,
    Price DECIMAL(10,2) NOT NULL CHECK (Price > 0),
    StockQuantity INT NOT NULL CHECK (StockQuantity >= 0),
    CategoryID INT NOT NULL,
    FOREIGN KEY (CategoryID) REFERENCES Categories(CategoryID)
);

-- 创建Orders表
CREATE TABLE Orders (
    OrderID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    CustomerID INT NOT NULL,
    OrderDate DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    TotalAmount DECIMAL(10,2) NOT NULL CHECK (TotalAmount > 0),
    FOREIGN KEY (CustomerID) REFERENCES Customers(CustomerID)
);

-- 创建OrderItems表
CREATE TABLE OrderItems (
    OrderItemID INT AUTO_INCREMENT PRIMARY KEY NOT NULL,
    OrderID INT NOT NULL,
    ProductID INT NOT NULL,
    Quantity INT NOT NULL CHECK (Quantity > 0),
    Subtotal DECIMAL(10,2) NOT NULL CHECK (Subtotal > 0),
    FOREIGN KEY (OrderID) REFERENCES Orders(OrderID),
    FOREIGN KEY (ProductID) REFERENCES Products(ProductID)
);

-- 添加计算Subtotal的触发器
DELIMITER $$
CREATE TRIGGER CalculateSubtotal
BEFORE INSERT ON OrderItems
FOR EACH ROW
BEGIN
    DECLARE product_price DECIMAL(10,2);
    SELECT Price INTO product_price FROM Products WHERE ProductID = NEW.ProductID;
    SET NEW.Subtotal = product_price * NEW.Quantity;
END$$
DELIMITER ;