#include <iostream>
#include <fstream>
#include <seal/seal.h>

using namespace std;
using namespace seal;

int main() {
    EncryptionParameters parms(scheme_type::bfv);
    parms.set_poly_modulus_degree(4096);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(4096));
    parms.set_plain_modulus(1024);
    SEALContext context(parms);

    // Load secret key (needed to decrypt)
    SecretKey secret_key;
    ifstream sk_in("secret.key", ios::binary);
    if (!sk_in) {
        cerr << "Error opening secret.key" << endl;
        return 1;
    }
    secret_key.load(context, sk_in);
    sk_in.close();

    // Load encrypted input
    Ciphertext encrypted_input;
    ifstream ct_in("input.ct", ios::binary);
    if (!ct_in) {
        cerr << "Error opening input.ct" << endl;
        return 1;
    }
    encrypted_input.load(context, ct_in);
    ct_in.close();

    // Evaluate: encrypted * 2 = encrypted + encrypted
    Evaluator evaluator(context);
    Ciphertext encrypted_result;
    evaluator.add(encrypted_input, encrypted_input, encrypted_result);

    // Decrypt result
    Decryptor decryptor(context, secret_key);
    Plaintext plain_result;
    decryptor.decrypt(encrypted_result, plain_result);

    // Convert plaintext to integer
    int result = stoi(plain_result.to_string());

    cout << "Server: Processed input (multiplied by 2). Result = " << result << endl;

    // Save result ciphertext if you want
    ofstream out("result.ct", ios::binary);
    if (!out) {
        cerr << "Error opening result.ct for writing" << endl;
        return 1;
    }
    encrypted_result.save(out);
    out.close();

    return 0;
}

