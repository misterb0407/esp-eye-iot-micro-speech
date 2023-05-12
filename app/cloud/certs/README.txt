Download the certificates from AWS IoT core. Then replace the content of:

Device/client certificate: *-certificate.pem -> client.crt
Client private key: *-private.pem.key -> client.key
Root CA certificates 2048 bits: AmazonRootCA1.pem -> server.crt


Note:
We don't need client public certificate in devices


