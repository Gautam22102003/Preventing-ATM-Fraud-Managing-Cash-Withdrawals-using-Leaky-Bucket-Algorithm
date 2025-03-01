# Preventing-ATM-Fraud-Managing-Cash-Withdrawals-using-Leaky-Bucket-Algorithm
A **C program** implementing the **Leaky Bucket Algorithm** for **ATM withdrawal rate limiting** to prevent fraud.  

### 🔹 **Concept**:
- Each user has a **withdrawal bucket**.
- The **leak rate** defines how often withdrawals are allowed (e.g., one transaction every 10 seconds).
- If too many withdrawals happen within a short time, further transactions are **blocked temporarily**.  

### **How It Works**
1. The **bucket size** (3) limits withdrawals in a short time.
2. **Old withdrawals leak** after **10 seconds** (LEAK_RATE).
3. If too many withdrawals happen quickly, the user is **blocked temporarily**.
4. The user can **try again after some time**.

### **Example Output**
```
ATM Withdrawal System
1. Withdraw Cash
2. Exit
Choose: 1
✅ Withdrawal successful! Remaining limit: 2

Choose: 1
✅ Withdrawal successful! Remaining limit: 1

Choose: 1
✅ Withdrawal successful! Remaining limit: 0

Choose: 1
❌ Too many withdrawals! Try again later.

(Waits 10 seconds...)
Choose: 1
✅ Withdrawal successful! Remaining limit: 2
```

---

### **Possible Enhancements**
✅ Set a **daily limit** on withdrawals.  
✅ Store user data in a **database or file**.  
✅ Implement **multi-user ATM simulation**.  
