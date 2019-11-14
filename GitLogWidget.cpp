#include "GitLogWidget.h"
#include <git2.h>
#include <iostream>

GitLogWidget::GitLogWidget(QWidget *parent) : QListWidget(parent) {
    git_libgit2_init();


    git_revwalk *walk;
    git_repository *repo;

    git_buf path = {};
    // FIXME: get the path from PWD
    if (git_repository_discover(&path, "/Users/ryandoyle/code/git-observer", 0, "/Users")) {
        const git_error *last_error = giterr_last();
        std::cerr <<__FILE__ << ":" << __LINE__ << " " << last_error->message;
        abort(); // FIXME: Check for a valid git dir before drawing MainWindow, shouldn't get here
    }

    if (git_repository_open(&repo, path.ptr)) {
        const git_error *last_error = giterr_last();
        std::cerr <<__FILE__ << ":" << __LINE__ << " " << last_error->message;
        abort(); // FIXME: Check we can open the repo beforehand
    }
    git_buf_free(&path);

    if (git_revwalk_new(&walk, repo)) {
        const git_error *last_error = giterr_last();
        std::cerr <<__FILE__ << ":" << __LINE__ << " " << last_error->message;
        abort(); // FIXME: what kind of errors get us into this condition?
    }

    git_revwalk_sorting(walk, GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME);
    git_revwalk_push_head(walk);

    git_oid oid;
    while (git_revwalk_next(&oid, walk) == 0) {
        git_commit *commit;
        git_commit_lookup(&commit, repo, &oid);

        char oidstr[10] = {0};
        git_oid_tostr(oidstr, 9, &oid);


        std::string commit_message(git_commit_summary(commit));
        std::string log_line;

        log_line.append(oidstr).append(": ").append(commit_message);



        this->addItem(QString::fromStdString(log_line));
        git_commit_free(commit);

    }
    git_revwalk_free(walk);
    git_repository_free(repo);
}

GitLogWidget::~GitLogWidget() {
    git_libgit2_shutdown();
}
