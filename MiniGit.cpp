void MiniGit::init() {
    std::cout << "Initializing MiniGit Repository...\n";

    // This creates the folders
    createDirectory(repoPath);
    createDirectory(objectsPath);
    createDirectory(repoPath + "/refs");
    createDirectory(commitsPath);

    // This creates the HEAD file to keep track of the current branch
    std::ofstream headFile(repoPath + "/HEAD");
    if (headFile) {
        headFile << "ref: refs/master\n";
        headFile.close();
        std::cout << "Initialized HEAD to master branch.\n";
    } else {
        std::cerr << "Failed to write HEAD file.\n";
    }
}
void MiniGit::commit(const std::string& message) {
    if (stagedFiles.empty()) {
        std::cout << "No changes to commit.\n";
        return;
    }

    Commit commit;
    commit.message = message;
    commit.timestamp = std::time(nullptr);
    commit.parentHash = headHash;

    for (const auto& file : stagedFiles) {
        commit.stagedFiles.push_back(file);
    }

    commit.hash = generateCommitHash(commit);
    saveCommit(commit);
    headHash = commit.hash;

    stagedFiles.clear();

    std::cout << "Committed with hash: " << commit.hash << "\n";
}

