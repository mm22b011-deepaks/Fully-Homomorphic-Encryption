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

    KeyGenerator keygen(context);
    PublicKey public_key;
    keygen.create_public_key(public_key);
    SecretKey secret_key = keygen.secret_key();

    // Save keys
    {
        ofstream pk_out("public.key", ios::binary);
        if (!pk_out) { cerr << "Error opening public.key\n"; return 1; }
        public_key.save(pk_out);
    }
    {
        ofstream sk_out("secret.key", ios::binary);
        if (!sk_out) { cerr << "Error opening secret.key\n"; return 1; }
        secret_key.save(sk_out);
    }

    int input;
    ifstream infile("number.txt");
    if (!infile) { cerr << "Error opening number.txt\n"; return 1; }
    infile >> input;

    // Encode integer as plaintext (use Plaintext directly)
    Plaintext plain(to_string(input));

    Encryptor encryptor(context, public_key);
    Ciphertext encrypted;
    encryptor.encrypt(plain, encrypted);

    ofstream ct_out("input.ct", ios::binary);
    if (!ct_out) { cerr << "Error opening input.ct\n"; return 1; }
    encrypted.save(ct_out);

    cout << "Client: Encrypted " << input << " and saved to input.ct\n";
    return 0;
}

